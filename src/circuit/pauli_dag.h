#ifndef CIRCUIT_PAULI_DAG_H_
#define CIRCUIT_PAULI_DAG_H_

#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

#include "helpers.h"
#include "pauli_exponential.h"
#include "stabiliser_tableau.h"

namespace qstabr {
namespace circuit {

class PauliDAG {
 public:
  PauliDAG();

  void AddPauli(PauliExponential &&pauli);

  void ExhaustiveRunner(const StabiliserTableau &tableau);

  void Print() const;

  size_t Size() const;

  void Synthesise(std::vector<SimpleGate> &gates,
                  const QubitManager &qubitManager);

  std::vector<SimpleClifford> SynthesiseCliffords(
      const QubitManager &qubitManager, int numQubits);

  void Reduce(const StabiliserTableau &tableau);

 private:
  void AddEdge(int a, int b);
  void RemoveEdge(int a, int b);

  void DFSTransitiveTraversal(std::unordered_set<int> &visited, int current);
  bool DFSCanReach(std::unordered_set<int> &visited, int current, int target);

  void MergePair(int a, int b, bool sign);
  void TryMergePair(int a, int b, const StabiliserTableau &tableau);
  void TryCancel(int a, const StabiliserTableau &tableau);
  bool CheckPhase(int a);
  void Reduce(int a, const StabiliserTableau &tableau);

  void RemovePauli(int a);

  std::vector<int> TopologicalSort() const;

  int nextIndex{};
  std::unordered_map<int, PauliExponential> paulis;
  std::unordered_map<int, std::unordered_set<int>> edges;
  std::unordered_map<int, std::unordered_set<int>> back_edges;
};

}  // namespace circuit
}  // namespace qstabr

#endif
