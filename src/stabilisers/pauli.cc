#include "pauli.h"

#include <cassert>
#include <string>

namespace qstabr {
namespace stabilisers {

PauliString::PauliString(bool sign, const std::vector<PauliLetter> &string)
    : sign(sign), string(string) {}

bool PauliString::DoesCommute(const PauliString &other) const {
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
  if (other.string.size() != string.size() || sign != other.sign) return false;
  for (size_t i{}; i < string.size(); i++) {
    if (other.string[i] != string[i]) return false;
  }
  return true;
}

size_t PauliStringHash::operator()(const PauliString &string) const {
  std::string strRep;
  strRep.resize(string.string.size() + 1);
  strRep[0] = string.sign ? '+' : '-';
  for (size_t i{}; i < string.string.size(); i++) {
    strRep[i + 1] = string.string[i];
  }
  return std::hash<std::string>()(strRep);
}

}  // namespace stabilisers
}  // namespace qstabr