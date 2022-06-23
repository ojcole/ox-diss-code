#ifndef CIRCUIT_STABILISER_TABLEAU_H
#define CIRCUIT_STABILISER_TABLEAU_H

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "helpers.h"
#include "pauli.h"
#include "phase/phase.h"
#include "qubit_manager.h"
#include "staq/qasmtools/ast/ast.hpp"

namespace qstabr {
namespace circuit {

class StabiliserTableau {
 public:
  StabiliserTableau(int qubits,
                    const std::shared_ptr<QubitManager> &qubitManger);
  StabiliserTableau(qasmtools::ast::Program &&program);

  void AddQubits(const std::string &name, int number);
  void ApplyUnitaryGate(const Qubit &qubit, const phase::RationalPhase &theta,
                        const phase::RationalPhase &phi,
                        const phase::RationalPhase &lambda);
  void ApplyZRot(const Qubit &qubit, const phase::RationalPhase &phase);
  void ApplyXRot(const Qubit &qubit, const phase::RationalPhase &phase);
  void ApplyHadamard(const Qubit &qubit);
  void ApplyCNOTGate(const Qubit &control, const Qubit &target);

  std::optional<bool> CanCreate(const PauliString &string) const;

  void Print() const;

 private:
  void GenerateTableau(qasmtools::ast::Program &normalisedProgram);

  int numQubits;
  std::vector<std::vector<int>> grid;

  std::shared_ptr<QubitManager> qubitManager;
};

}  // namespace circuit
}  // namespace qstabr

#endif
