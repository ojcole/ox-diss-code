#ifndef CIRCUIT_PAULI_STRING_H_
#define CIRCUIT_PAULI_STRING_H_

#include <array>
#include <iostream>
#include <vector>

namespace qstabr {
namespace circuit {

enum PauliLetter : char {
  I = 'I',
  Z = 'Z',
  X = 'X',
  Y = 'Y',
};

constexpr std::array<PauliLetter, 3> ACTIVE_LETTERS{Z, X, Y};

inline std::vector<PauliLetter> operator"" _p(const char *str, size_t len) {
  std::vector<PauliLetter> letters(len, I);
  for (size_t i{}; i < len; i++) {
    if (str[i] == 'Z') {
      letters[i] = Z;
    } else if (str[i] == 'X') {
      letters[i] = X;
    } else if (str[i] == 'Y') {
      letters[i] = Y;
    }
  }
  return letters;
}

class PauliExponential;

class PauliString {
 public:
  PauliString(const std::vector<PauliLetter> &string, bool negated = false);

  bool CommutesWith(const PauliString &other) const;

  std::vector<int> GetMatrixForm() const;
  std::vector<PauliString> StringDecomps() const;

  void Negate();
  bool IsNegated() const;

  bool operator==(const PauliString &other) const;
  void operator*=(const PauliString &other);

  const PauliLetter &operator[](size_t index) const { return string[index]; }
  int size() const { return static_cast<int>(string.size()); }

  std::vector<int> Weight() const;
  int NonZWeight() const;

  static PauliString StringDifference(const PauliString &string1,
                                      const PauliString &string2);
  static std::pair<bool, PauliString> StringMultiply(
      const PauliString &string1, const PauliString &string2);
  static bool StringMultiplySign(const PauliString &string1,
                                 const PauliString &string2);

 private:
  PauliLetter &operator[](size_t index) { return string[index]; }

  std::vector<PauliLetter> string;
  bool negated = false;

  friend class PauliExponential;
};

inline std::ostream &operator<<(std::ostream &stream,
                                const PauliString &string) {
  if (string.IsNegated()) {
    stream << "-";
  } else {
    stream << "+";
  }
  for (int i{}; i < string.size(); i++) {
    stream << static_cast<char>(string[i]);
  }
  return stream;
}

PauliString operator*(const PauliString &string1, const PauliString &string2);

}  // namespace circuit
}  // namespace qstabr

#endif