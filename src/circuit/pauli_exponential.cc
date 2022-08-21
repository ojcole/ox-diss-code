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
    : string(string), phaseExpr(std::move(phaseExpr)) {}

bool PauliExponential::CommutesWith(const PauliExponential &other) const {
  return string.CommutesWith(other.string);
}

void PauliExponential::PushCliffordThrough(const CliffordGate &gate) {
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

void PauliExponential::Negate() { string.Negate(); }

bool PauliExponential::IsNegated() const { return string.IsNegated(); }

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
  if (IsNegated() == other.IsNegated()) {
    auto newPhase = AddExprPhases(*phaseExpr, *other.phaseExpr);
    phaseExpr = std::move(newPhase);
  } else {
    auto newPhase = SubtractExprPhases(*phaseExpr, *other.phaseExpr);
    phaseExpr = std::move(newPhase);
  }
}

void PauliExponential::ApplyPauliStabiliser(const PauliString &other) {
  string *= other;
}

void PauliExponential::SetPauliString(PauliString newString) {
  string = std::move(newString);
}

bool PauliExponential::DiagAtQubit(int qubit) const {
  return string[qubit] == I || string[qubit] == Z;
}

void PauliExponential::DiagonaliseQubit(int qubit) {
  if (string[qubit] != I) string[qubit] = Z;
}

staq::synthesis::phase_term PauliExponential::ToPhaseTerm() {
  std::vector<bool> qubits(string.size(), false);
  auto weights = string.Weight();
  for (const auto qubit : weights) {
    qubits[qubit] = true;
  }
  if (IsNegated()) {
    phaseExpr = NegateExprPhase(*phaseExpr);
  }
  return {qubits, std::move(phaseExpr)};
}

void PauliExponential::ReduceToZ(int qubit) {
  std::vector<PauliLetter> newString(string.size(), I);
  newString[qubit] = Z;
  string = {newString, IsNegated()};
}

const PauliString &PauliExponential::GetString() const { return string; }

std::vector<int> PauliExponential::GetMatrixForm() const {
  return string.GetMatrixForm();
}

qasmtools::ast::Expr &PauliExponential::GetExpr() const { return *phaseExpr; }

void PauliExponential::Print() const {
  phaseExpr->pretty_print(std::cout);
  std::cout << " " << string << std::endl;
}

namespace {

void SynthesisePhasePoly(std::vector<SimpleGate> &gates,
                         const PauliString &string, double value, int i = 0) {
  if (i >= string.size()) return;
  if (string[i] == I) {
    SynthesisePhasePoly(gates, string, value, i + 1);
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
  SynthesisePhasePoly(gates, string, value, next_i);
  gates.push_back(CliffordGate::CreateCNOT(i, next_i));
}

}  // namespace

void PauliExponential::Synthesise(std::vector<SimpleGate> &gates) const {
  std::optional<double> value = phaseExpr->constant_eval();
  if (!value.has_value()) return;
  double val = *value;
  if (IsNegated()) val *= -1;
  for (int i{}; i < string.size(); i++) {
    if (string[i] == X) {
      gates.push_back(CliffordGate::CreateHAD(i));
    } else if (string[i] == Y) {
      gates.push_back(CliffordGate::CreateXRot(i, phase::PI_BY_2));
    }
  }
  SynthesisePhasePoly(gates, string, val);
  for (int i{}; i < string.size(); i++) {
    if (string[i] == X) {
      gates.push_back(CliffordGate::CreateHAD(i));
    } else if (string[i] == Y) {
      gates.push_back(CliffordGate::CreateXRot(i, phase::MINUS_PI_BY_2));
    }
  }
}

std::optional<std::vector<CliffordGate>>
PauliExponential::GetCliffordRepresentation() {
  std::optional<double> value = phaseExpr->constant_eval();
  if (!value.has_value()) return std::nullopt;
  if (IsNegated()) *value *= -1;
  std::optional<phase::RationalPhase> phase = CliffordPhaseFromDouble(*value);
  if (!phase.has_value()) return std::nullopt;
  std::vector<CliffordGate> cliffordGates;
  std::vector<SimpleGate> gates;
  Synthesise(gates);
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
