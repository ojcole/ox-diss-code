#ifndef CIRCUIT_PAULI_EXPONENTIAL_H_
#define CIRCUIT_PAULI_EXPONENTIAL_H_

#include <cstddef>
#include <iostream>
#include <vector>

#include "clifford_gate.h"
#include "helpers.h"
#include "pauli_string.h"
#include "qubit_manager.h"
#include "staq/qasmtools/ast/expr.hpp"

namespace qstabr {
namespace circuit {

class PauliExponential {
 public:
  PauliExponential(const PauliString &string,
                   std::unique_ptr<qasmtools::ast::Expr> phase);

  bool CommutesWith(const PauliExponential &other) const;

  bool CommutesWithPauli(const PauliString &pauliString) const;

  void PushCliffordThrough(const CliffordGate &gate,
                           const QubitManager &qubitManager);

  void CombineWithPauli(const PauliExponential &other);

  void ApplyString(const PauliString &pauliString, bool sign);

  std::vector<int> GetMatrixForm() const;

  void Print() const {
    std::cout << "Negated: " << negated << std::endl;
    string.Print();
    phaseExpr->pretty_print(std::cout) << std::endl;
  }

  void Negate();

  bool IsNegated() const;

  PauliString GetString() const;

  qasmtools::ast::Expr &GetExpr() const;

  void Synthesise(std::vector<SimpleGate> &gates,
                  const QubitManager &manager) const;

  std::optional<std::vector<CliffordGate>> GetCliffordRepresentation(
      const QubitManager &manager);

 private:
  void ApplyHadamard(int qubit);
  void ApplyCNOT(int control, int target);
  void ApplySGate(int qubit);

  PauliString string;
  std::unique_ptr<qasmtools::ast::Expr> phaseExpr;
  bool negated;
};

}  // namespace circuit
}  // namespace qstabr

#endif
