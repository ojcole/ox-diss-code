#ifndef CIRCUIT_PAULI_H_
#define CIRCUIT_PAULI_H_

#include <cstddef>
#include <vector>

#include "clifford_gate.h"
#include "staq/qasmtools/ast/expr.hpp"

namespace qstabr {
namespace circuit {

enum PauliLetter : char {
  I = 'I',
  Z = 'Z',
  X = 'X',
  Y = 'Y',
};

class PauliStringHash;

class PauliString {
 public:
  PauliString(const std::vector<PauliLetter> &string);

  bool CommutesWith(const PauliString &other) const;

  bool operator==(const PauliString &other) const;

 private:
  const std::vector<PauliLetter> string;

  friend class PauliStringHash;
};

class PauliExponential {
 public:
  PauliExponential(const PauliString &string,
                   std::unique_ptr<qasmtools::ast::Expr> phase);

  bool CommutesWith(const PauliExponential &other) const;
  void PushCliffordThrough(const CliffordGate &gate);

 private:
  PauliString string;
  std::unique_ptr<qasmtools::ast::Expr> phase;
};

class PauliStringHash {
  size_t operator()(const PauliString &string) const;
};

}  // namespace circuit
}  // namespace qstabr

#endif