#include "pauli.h"

#include <cassert>
#include <string>

namespace qstabr {
namespace circuit {

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
    : string(string), phase(std::move(phase)) {}

bool PauliExponential::CommutesWith(const PauliExponential &other) const {
  return string.CommutesWith(other.string);
}

void PauliExponential::PushCliffordThrough(const CliffordGate &gate) {}

}  // namespace circuit
}  // namespace qstabr