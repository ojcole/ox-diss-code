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
#include "staq/synthesis/cnot_dihedral.hpp"

namespace qstabr {
namespace circuit {

class PauliExponential {
 public:
  PauliExponential(const PauliString &string,
                   std::unique_ptr<qasmtools::ast::Expr> phase);

  bool CommutesWith(const PauliExponential &other) const;

  void PushCliffordThrough(const CliffordGate &gate);

  void CombineWithPauli(const PauliExponential &other);

  void ApplyPauliStabiliser(const PauliString &other);

  bool DiagAtQubit(int qubit) const;

  void DiagonaliseQubit(int qubit);

  staq::synthesis::phase_term ToPhaseTerm();

  void ReduceToZ(int qubit);

  std::vector<int> GetMatrixForm() const;

  void Print() const {
    phaseExpr->pretty_print(std::cout);
    std::cout << " ";
    string.Print();
  }

  void Negate();

  bool IsNegated() const;

  const PauliString &GetString() const;

  qasmtools::ast::Expr &GetExpr() const;

  void Synthesise(std::vector<SimpleGate> &gates) const;

  std::optional<std::vector<CliffordGate>> GetCliffordRepresentation();

 private:
  void ApplyHadamard(int qubit);
  void ApplyCNOT(int control, int target);
  void ApplySGate(int qubit);

  PauliString string;
  std::unique_ptr<qasmtools::ast::Expr> phaseExpr;
};

}  // namespace circuit
}  // namespace qstabr

#endif
