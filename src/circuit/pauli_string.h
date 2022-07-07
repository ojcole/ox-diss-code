#ifndef CIRCUIT_PAULI_STRING_H_
#define CIRCUIT_PAULI_STRING_H_

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

class PauliStringHash;
class PauliExponential;

class PauliString {
 public:
  PauliString(const std::vector<PauliLetter> &string);

  bool CommutesWith(const PauliString &other) const;

  bool operator==(const PauliString &other) const;

  std::vector<int> GetMatrixForm() const;

  void Print() const {
    for (auto letter : string) {
      std::cout << static_cast<char>(letter);
    }
    std::cout << std::endl;
  }

  std::vector<PauliString> StringDecomps() const;

  static PauliString StringDifference(const PauliString &string1,
                                      const PauliString &string2);

  const PauliLetter &operator[](size_t index) const { return string[index]; }
  size_t size() const { return string.size(); }

 private:
  PauliLetter &operator[](size_t index) { return string[index]; }

  std::vector<PauliLetter> string;

  friend class PauliStringHash;
  friend class PauliExponential;
};

class PauliStringHash {
  size_t operator()(const PauliString &string) const;
};

}  // namespace circuit
}  // namespace qstabr

#endif