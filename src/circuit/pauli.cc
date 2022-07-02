#include "pauli.h"

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

PauliString::PauliString(const std::vector<PauliLetter> &string)
    : string(string) {}

bool PauliString::CommutesWith(const PauliString &other) const {
  assert(other.string.size() == string.size());

  int anticommute{};
  for (size_t i{}; i < string.size(); i++) {
    if (string[i] != other.string[i] && string[i] != I &&
        other.string[i] != I) {
      anticommute++;
    }
  }

  return (anticommute & 1) == 0;
}

bool PauliString::operator==(const PauliString &other) const {
  if (other.string.size() != string.size()) return false;
  for (size_t i{}; i < string.size(); i++) {
    if (other.string[i] != string[i]) return false;
  }
  return true;
}

std::vector<int> PauliString::GetMatrixForm() const {
  std::vector<int> mat;
  mat.resize(string.size() * 2);
  for (size_t i{}; i < string.size(); i++) {
    if (string[i] == Z) {
      mat[i] = 0;
      mat[i + string.size()] = 1;
    } else if (string[i] == X) {
      mat[i] = 1;
      mat[i + string.size()] = 0;
    } else if (string[i] == Y) {
      mat[i] = 1;
      mat[i + string.size()] = 1;
    }
  }

  return mat;
}

PauliString PauliString::StringDifference(const PauliString &string1,
                                          const PauliString &string2) {
  assert(string1.size() == string2.size());
  std::vector<PauliLetter> newString(string1.size(), I);
  for (size_t i{}; i < string1.size(); i++) {
    if (string1[i] == I) {
      newString[i] = string2[i];
    } else if (string2[i] == I) {
      newString[i] = string1[i];
    } else if (string1[i] == Z) {
      if (string2[i] == X) {
        newString[i] = Y;
      } else if (string2[i] == Y) {
        newString[i] = X;
      }
    } else if (string1[i] == X) {
      if (string2[i] == Z) {
        newString[i] = Y;
      } else if (string2[i] == Y) {
        newString[i] = Z;
      }
    } else if (string1[i] == Y) {
      if (string2[i] == Z) {
        newString[i] = X;
      } else if (string2[i] == X) {
        newString[i] = Z;
      }
    }
  }
  return newString;
}

size_t PauliStringHash::operator()(const PauliString &string) const {
  std::string strRep;
  strRep.resize(string.string.size());
  for (size_t i{}; i < string.string.size(); i++) {
    strRep[i] = string.string[i];
  }
  return std::hash<std::string>()(strRep);
}

PauliExponential::PauliExponential(
    const PauliString &string, std::unique_ptr<qasmtools::ast::Expr> phaseExpr)
    : string(string), phaseExpr(std::move(phaseExpr)), negated(false) {}

bool PauliExponential::CommutesWith(const PauliExponential &other) const {
  return string.CommutesWith(other.string);
}

bool PauliExponential::CommutesWithPauli(const PauliString &pauliString) const {
  assert(string.size() == pauliString.size());
  for (size_t i{}; i < string.size(); i++) {
    if (string[i] != I && pauliString[i] != I && string[i] != pauliString[i]) {
      return false;
    }
  }
  return true;
}

void PauliExponential::PushCliffordThrough(
    const CliffordGate &gate,
    const std::shared_ptr<QubitManager> &qubitManager) {
  const auto type = gate.GetGateType();
  int firstQubit = qubitManager->GetQubitIndex(gate.GetFirstQubit());

  if (type == GateType::HAD) {
    ApplyHadamard(firstQubit);
  } else if (type == GateType::CNOT) {
    int secondQubit = qubitManager->GetQubitIndex(gate.GetSecondQubit());
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

PauliString PauliExponential::GetString() const { return string; }

std::vector<int> PauliExponential::GetMatrixForm() const {
  return string.GetMatrixForm();
}

qasmtools::ast::Expr &PauliExponential::GetExpr() const { return *phaseExpr; }

namespace {

void SynthesisePhasePoly(std::ostream &output, const QubitManager &manager,
                         const PauliString &string, double value,
                         size_t i = 0UL) {
  if (i >= string.size()) return;
  if (string[i] == I) {
    SynthesisePhasePoly(output, manager, string, value, i + 1);
    return;
  }
  size_t next_i{i + 1};
  for (; next_i <= string.size(); next_i++) {
    if (string[next_i] != I) break;
  }

  const auto &qubit = manager.GetIndexQubit(i);
  if (next_i >= string.size()) {
    std::streamsize ss = output.precision();
    output << "u1(" << std::setprecision(15) << value << std::setprecision(ss)
           << ") " << qubit.name << "[" << qubit.offset << "];" << std::endl;
    return;
  }

  const auto &nextQubit = manager.GetIndexQubit(next_i);
  output << "cx " << qubit.name << "[" << qubit.offset << "], "
         << nextQubit.name << "[" << nextQubit.offset << "];" << std::endl;
  SynthesisePhasePoly(output, manager, string, value, next_i);
  output << "cx " << qubit.name << "[" << qubit.offset << "], "
         << nextQubit.name << "[" << nextQubit.offset << "];" << std::endl;
}
}  // namespace

void PauliExponential::Synthesise(std::ostream &output,
                                  const QubitManager &manager) {
  std::optional<double> value = phaseExpr->constant_eval();
  if (!value.has_value()) return;
  double val = *value;
  if (negated) val *= -1;
  for (size_t i{}; i < string.size(); i++) {
    const auto &qubit = manager.GetIndexQubit(i);
    if (string[i] == X) {
      output << "h " << qubit.name << "[" << qubit.offset << "];" << std::endl;
    } else if (string[i] == Y) {
      // output << "sx " << qubit.name << "[" << qubit.offset << "];" <<
      // std::endl;
      output << "h " << qubit.name << "[" << qubit.offset << "];" << std::endl;
      output << "s " << qubit.name << "[" << qubit.offset << "];" << std::endl;
      output << "h " << qubit.name << "[" << qubit.offset << "];" << std::endl;
    }
  }
  SynthesisePhasePoly(output, manager, string, val);
  for (size_t i{}; i < string.size(); i++) {
    const auto &qubit = manager.GetIndexQubit(i);
    if (string[i] == X) {
      output << "h " << qubit.name << "[" << qubit.offset << "];" << std::endl;
    } else if (string[i] == Y) {
      // output << "sxdg " << qubit.name << "[" << qubit.offset << "];"
      //        << std::endl;
      output << "h " << qubit.name << "[" << qubit.offset << "];" << std::endl;
      output << "sdg " << qubit.name << "[" << qubit.offset << "];"
             << std::endl;
      output << "h " << qubit.name << "[" << qubit.offset << "];" << std::endl;
    }
  }
}

}  // namespace circuit
}  // namespace qstabr
