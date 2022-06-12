#ifndef STABILISERS_PAULI_H_
#define STABILISERS_PAULI_H_

#include <cstddef>
#include <vector>

namespace qstabr {
namespace stabilisers {

enum PauliLetter : char {
  I = 'I',
  Z = 'Z',
  X = 'X',
  Y = 'Y',
};

class PauliStringHash;

class PauliString {
 public:
  PauliString(bool sign, const std::vector<PauliLetter> &string);

  bool DoesCommute(const PauliString &other) const;

  bool operator==(const PauliString &other) const;

 private:
  bool sign;
  const std::vector<PauliLetter> string;

  friend class PauliStringHash;
};

class PauliStringHash {
  size_t operator()(const PauliString &string) const;
};

}  // namespace stabilisers
}  // namespace qstabr

#endif