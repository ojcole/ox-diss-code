#ifndef CIRCUIT_PAULI_CIRCUIT_H_
#define CIRCUIT_PAULI_CIRCUIT_H_

#include <variant>
#include <vector>

#include "clifford_gate.h"
#include "helpers.h"
#include "pauli_dag.h"
#include "pauli_exponential.h"
#include "stabiliser_tableau.h"
#include "staq/qasmtools/ast/program.hpp"

namespace qstabr {
namespace circuit {

class PauliCircuit {
 public:
  using Gate = std::variant<CliffordGate, PauliExponential>;

  PauliCircuit(qasmtools::ast::Program &&program);

  void AddQubits(const std::string &name, int number);
  void AddZPauliExp(const Qubit &qubit,
                    std::unique_ptr<qasmtools::ast::Expr> phase);
  void AddXPauliExp(const Qubit &qubit,
                    std::unique_ptr<qasmtools::ast::Expr> phase);
  void AddHadamard(const Qubit &qubit);
  void AddZRot(const Qubit &qubit, const phase::RationalPhase &phase);
  void AddXRot(const Qubit &qubit, const phase::RationalPhase &phase);
  void AddCNOTGate(const Qubit &control, const Qubit &target);

  void Synthesise(std::ostream &output, const SynthOptions &options = {});

  size_t PauliCount() const;

  void Optimise(int threads = 1);

  void PrintDAG() const;

  struct GateOptStats {
    int originalGateCount;
    int originalCNOTCount;
    int resultingGateCount;
    int resultingCNOTCount;
  };

  struct FullStats {
    GateOptStats GateStats;
    PauliDAG::OptStats DAGStats;
  };

  FullStats GetOptStats() const;

 private:
  void ProcessGates();
  void ProcessGates2();
  void ProcessGates3();

  std::vector<SimpleClifford> OptimiseCliffords(std::vector<SimpleGate> &gates,
                                                int threads) const;

  void ReconstructDAG(PauliDAG &dag) const;

  std::shared_ptr<QubitManager> qubitManager;

  StabiliserTableau tableau;
  PauliDAG pauli_graph;
  std::vector<Gate> gates;

  int numQubits;

  int originalGateCount{};
  int originalCNOTCount{};
  int resultingGateCount{};
  int resultingCNOTCount{};
};

}  // namespace circuit
}  // namespace qstabr

#endif