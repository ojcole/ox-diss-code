#include "pauli_string.h"

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

std::pair<bool, PauliString> PauliString::StringMultiply(
    const PauliString &string1, const PauliString &string2) {
  return {StringMultiplySign(string1, string2),
          StringDifference(string1, string2)};
}

bool PauliString::StringMultiplySign(const PauliString &string1,
                                     const PauliString &string2) {
  int iCount{};
  bool sign{false};
  for (size_t i{}; i < string1.size(); i++) {
    if (string1[i] == X) {
      if (string2[i] == Z) {
        iCount--;
      } else if (string2[i] == Y) {
        iCount++;
      }
    } else if (string1[i] == Z) {
      if (string2[i] == X) {
        iCount--;
        sign = !sign;
      } else if (string2[i] == Y) {
        iCount++;
        sign = !sign;
      }
    } else if (string1[i] == Y) {
      if (string2[i] == Z) {
        iCount++;
      } else if (string2[i] == X) {
        iCount++;
        sign = !sign;
      }
    }
  }
  assert(iCount % 2 == 0);
  if (iCount % 4 != 0) sign = !sign;
  return sign;
}

std::vector<PauliString> PauliString::StringDecomps() const {
  std::vector<PauliString> result;
  std::vector<PauliLetter> newString(string.size(), I);
  for (size_t i{}; i < string.size(); i++) {
    newString[i] = string[i];
    if (newString[i] != I) result.push_back(newString);
    newString[i] = I;
  }
  return result;
}

}  // namespace circuit
}  // namespace qstabr