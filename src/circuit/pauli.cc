#include "pauli.h"

#include <cassert>
#include <map>
#include <string>

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
    {I, {I, false}}, {X, {Y, true}}, {Z, {Z, false}}, {Y, {X, false}}};

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

size_t PauliStringHash::operator()(const PauliString &string) const {
  std::string strRep;
  strRep.resize(string.string.size());
  for (size_t i{}; i < string.string.size(); i++) {
    strRep[i] = string.string[i];
  }
  return std::hash<std::string>()(strRep);
}

PauliExponential::PauliExponential(const PauliString &string,
                                   std::unique_ptr<qasmtools::ast::Expr> phase)
    : string(string), phase(std::move(phase)), negated(false) {}

bool PauliExponential::CommutesWith(const PauliExponential &other) const {
  return string.CommutesWith(other.string);
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
    const auto &phase = *gate.GetPhase();

    if (type == GateType::XROT) {
      ApplyHadamard(firstQubit);
    }

    int iters = (static_cast<int>(phase / phase::PI_BY_2) + 4) % 4;
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

}  // namespace circuit
}  // namespace qstabr