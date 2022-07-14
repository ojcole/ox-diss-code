#ifndef CIRCUIT_STABILISER_TABLEAU_H
#define CIRCUIT_STABILISER_TABLEAU_H

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "helpers.h"
#include "pauli_exponential.h"
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
  void ApplyPhase(const Qubit &qubit);
  void ApplyXRot(const Qubit &qubit, const phase::RationalPhase &phase);
  void ApplyHadamard(const Qubit &qubit);
  void ApplyCNOTGate(const Qubit &control, const Qubit &target);
  void ApplyCliffordGate(const CliffordGate &clifford);

  inline bool operator==(const StabiliserTableau &other) {
    if (numQubits != other.numQubits) return false;
    for (int i{numQubits}; i < 2 * numQubits; i++) {
      for (int j{}; j < 2 * numQubits + 1; j++) {
        if (grid[i][j] != other.grid[i][j]) return false;
      }
    }
    return true;
  }

  std::optional<bool> CanCreate(const PauliString &string) const;

  void Print() const;

  void Synthesise(std::vector<SimpleGate> &gates);

 private:
  void ApplyZRot(int qubit, const phase::RationalPhase &phase);
  void ApplyPhase(int qubit);
  void ApplyHadamard(int qubit);
  void ApplyCNOTGate(int control, int target);

  void GenerateTableau(qasmtools::ast::Program &normalisedProgram);

  PauliString GetString(int index) const;

  enum SynthGateType {
    HAD,
    PHASE,
    CNOT,
  };

  struct SynthGate {
    SynthGateType type;
    int qubit1;
    int qubit2 = -1;
  };

  using SynthVec = std::vector<SynthGate>;

  void MakeCFullRank(SynthVec &output);
  void EliminateC(SynthVec &output, int rowOffset, int colOffset);
  void MMStab(SynthVec &output, int rowOffset, int colOffset);
  void ClearM(SynthVec &output, int rowOffset, int colOffset);
  void CancelGates(SynthVec &gates);

  int numQubits;
  std::vector<std::vector<int>> grid;

  std::shared_ptr<QubitManager> qubitManager;
};

}  // namespace circuit
}  // namespace qstabr

#endif
