#ifndef CIRCUIT_PAULI_H_
#define CIRCUIT_PAULI_H_

#include <cstddef>
#include <iostream>
#include <vector>

#include "clifford_gate.h"
#include "qubit_manager.h"
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
class PauliExponential;

class PauliString {
 public:
  PauliString(const std::vector<PauliLetter> &string);

  bool CommutesWith(const PauliString &other) const;

  bool operator==(const PauliString &other) const;

  void Print() const {
    for (auto letter : string) {
      std::cout << static_cast<char>(letter);
    }
    std::cout << std::endl;
  }

 private:
  PauliLetter &operator[](size_t index) { return string[index]; }

  std::vector<PauliLetter> string;

  friend class PauliStringHash;
  friend class PauliExponential;
};

class PauliExponential {
 public:
  PauliExponential(const PauliString &string,
                   std::unique_ptr<qasmtools::ast::Expr> phase);

  bool CommutesWith(const PauliExponential &other) const;

  void PushCliffordThrough(const CliffordGate &gate,
                           const std::shared_ptr<QubitManager> &qubitManager);

  void Print() const {
    std::cout << "Negated: " << negated << std::endl;
    string.Print();
    phase->pretty_print(std::cout) << std::endl;
  }

  void Negate();

 private:
  void ApplyHadamard(int qubit);
  void ApplyCNOT(int control, int target);
  void ApplySGate(int qubit);

  PauliString string;
  std::unique_ptr<qasmtools::ast::Expr> phase;
  bool negated;
};

class PauliStringHash {
  size_t operator()(const PauliString &string) const;
};

}  // namespace circuit
}  // namespace qstabr

#endif