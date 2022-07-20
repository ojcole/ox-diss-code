#include "pauli_exponential.h"

#include <cassert>
#include <map>
#include <string>

#include "helpers.h"

namespace qstabr {
namespace circuit {

namespace {

struct SingleQubitMapping {
  PauliLetter image;
  bool negates;
};

const std::map<PauliLetter, SingleQubitMapping> hadamardMapping{
    {I, {I, false}}, {X, {Z, false}}, {Z, {X, false}}, {Y, {Y, true}}};

const std::map<PauliLetter, SingleQubitMapping> sgateMapping{
    {I, {I, false}}, {X, {Y, false}}, {Z, {Z, false}}, {Y, {X, true}}};

struct MultiQubitMapping {
  PauliLetter imageFirst;
  PauliLetter imageSecond;
  bool negates;
};

const std::map<std::pair<PauliLetter, PauliLetter>, MultiQubitMapping>
    cnotMapping{
        {{X, I}, {X, X, false}}, {{I, X}, {I, X, false}},
        {{X, Z}, {Y, Y, true}},  {{Z, X}, {Z, X, false}},
        {{X, X}, {X, I, false}}, {{X, Y}, {Y, Z, false}},
        {{Y, X}, {Y, I, false}}, {{Z, I}, {Z, I, false}},
        {{I, Z}, {Z, Z, false}}, {{Z, Y}, {I, Y, false}},
        {{Y, Z}, {X, Y, false}}, {{Z, Z}, {I, Z, false}},
        {{Y, Y}, {X, Z, true}},  {{Y, I}, {Y, X, false}},
        {{I, Y}, {Z, Y, false}},
    };

}  // namespace

PauliExponential::PauliExponential(
    const PauliString &string, std::unique_ptr<qasmtools::ast::Expr> phaseExpr)
    : string(string), phaseExpr(std::move(phaseExpr)), negated(false) {}

bool PauliExponential::CommutesWith(const PauliExponential &other) const {
  return string.CommutesWith(other.string);
}

bool PauliExponential::CommutesWithPauli(const PauliString &pauliString) const {
  assert(string.size() == pauliString.size());
  for (int i{}; i < string.size(); i++) {
    if (string[i] != I && pauliString[i] != I && string[i] != pauliString[i]) {
      return false;
    }
  }
  return true;
}

void PauliExponential::PushCliffordThrough(const CliffordGate &gate,
                                           const QubitManager &qubitManager) {
  const auto type = gate.GetGateType();
  int firstQubit = gate.GetFirstQubit();

  if (type == GateType::HAD) {
    ApplyHadamard(firstQubit);
  } else if (type == GateType::CNOT) {
    int secondQubit = gate.GetSecondQubit();
    ApplyCNOT(firstQubit, secondQubit);
  } else {
    const auto &rationalPhase = *gate.GetPhase();

    if (type == GateType::XROT) {
      ApplyHadamard(firstQubit);
    }

    int iters = (static_cast<int>(rationalPhase.GetFraction() /
                                  phase::PI_BY_2.GetFraction()) +
                 4) %
                4;
    for (int j{}; j < iters; j++) {
      ApplySGate(firstQubit);
    }

    if (type == GateType::XROT) {
      ApplyHadamard(firstQubit);
    }
  }
}

void PauliExponential::Negate() { negated = !negated; }

bool PauliExponential::IsNegated() const { return negated; }

void PauliExponential::ApplyHadamard(int qubit) {
  auto it = hadamardMapping.find(string[qubit]);
  if (it != hadamardMapping.end()) {
    string[qubit] = it->second.image;
    if (it->second.negates) Negate();
  }
}

void PauliExponential::ApplyCNOT(int control, int target) {
  auto it = cnotMapping.find({string[control], string[target]});
  if (it != cnotMapping.end()) {
    auto mapping = it->second;
    string[control] = mapping.imageFirst;
    string[target] = mapping.imageSecond;
    if (mapping.negates) Negate();
  }
}

void PauliExponential::ApplySGate(int qubit) {
  auto it = sgateMapping.find(string[qubit]);
  if (it != sgateMapping.end()) {
    string[qubit] = it->second.image;
    if (it->second.negates) Negate();
  }
}

void PauliExponential::CombineWithPauli(const PauliExponential &other) {
  if (negated == other.negated) {
    auto newPhase = AddExprPhases(*phaseExpr, *other.phaseExpr);
    phaseExpr = std::move(newPhase);
  } else {
    auto newPhase = SubtractExprPhases(*phaseExpr, *other.phaseExpr);
    phaseExpr = std::move(newPhase);
  }
}

void PauliExponential::ApplyString(const PauliString &pauliString, bool sign) {
  string = PauliString::StringDifference(string, pauliString);
  if (sign) {
    Negate();
  }
}

PauliString PauliExponential::GetString() const { return string; }

std::vector<int> PauliExponential::GetMatrixForm() const {
  return string.GetMatrixForm();
}

qasmtools::ast::Expr &PauliExponential::GetExpr() const { return *phaseExpr; }

namespace {

void SynthesisePhasePoly(std::vector<SimpleGate> &gates,
                         const QubitManager &manager, const PauliString &string,
                         double value, int i = 0) {
  if (i >= string.size()) return;
  if (string[i] == I) {
    SynthesisePhasePoly(gates, manager, string, value, i + 1);
    return;
  }
  int next_i{i + 1};
  for (; next_i < string.size(); next_i++) {
    if (string[next_i] != I) break;
  }

  if (next_i >= string.size()) {
    gates.push_back(ZGate(i, value));
    return;
  }

  gates.push_back(CliffordGate::CreateCNOT(i, next_i));
  SynthesisePhasePoly(gates, manager, string, value, next_i);
  gates.push_back(CliffordGate::CreateCNOT(i, next_i));
}

}  // namespace

void PauliExponential::Synthesise(std::vector<SimpleGate> &gates,
                                  const QubitManager &manager) const {
  std::optional<double> value = phaseExpr->constant_eval();
  if (!value.has_value()) return;
  double val = *value;
  if (negated) val *= -1;
  for (int i{}; i < string.size(); i++) {
    if (string[i] == X) {
      gates.push_back(CliffordGate::CreateHAD(i));
    } else if (string[i] == Y) {
      gates.push_back(
          CliffordGate::CreateXRot(i, phase::RationalPhase({1, 2})));
    }
  }
  SynthesisePhasePoly(gates, manager, string, val);
  for (int i{}; i < string.size(); i++) {
    if (string[i] == X) {
      gates.push_back(CliffordGate::CreateHAD(i));
    } else if (string[i] == Y) {
      gates.push_back(
          CliffordGate::CreateXRot(i, phase::RationalPhase({-1, 2})));
    }
  }
}

std::optional<std::vector<CliffordGate>>
PauliExponential::GetCliffordRepresentation(const QubitManager &manager) {
  std::optional<double> value = phaseExpr->constant_eval();
  if (!value.has_value()) return std::nullopt;
  if (negated) *value *= -1;
  std::optional<phase::RationalPhase> phase = CliffordPhaseFromDouble(*value);
  if (!phase.has_value()) return std::nullopt;
  std::vector<CliffordGate> cliffordGates;
  std::vector<SimpleGate> gates;
  Synthesise(gates, manager);
  for (const auto &gate : gates) {
    if (std::holds_alternative<CliffordGate>(gate)) {
      cliffordGates.push_back(std::get<CliffordGate>(std::move(gate)));
    } else {
      assert(std::holds_alternative<ZGate>(gate));
      auto qubit = std::get<ZGate>(gate).GetQubit();
      cliffordGates.push_back(CliffordGate::CreateZRot(qubit, *phase));
    }
  }
  return cliffordGates;
}

}  // namespace circuit
}  // namespace qstabr
