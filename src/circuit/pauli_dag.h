#ifndef CIRCUIT_PAULI_DAG_H_
#define CIRCUIT_PAULI_DAG_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pauli.h"
#include "stabiliser_tableau.h"

namespace qstabr {
namespace circuit {

class PauliDAG {
 public:
  PauliDAG();

  void AddPauli(PauliExponential &&pauli);

  void Runner(const StabiliserTableau &tableau);

  void Print() const;

 private:
  void AddEdge(int a, int b);
  void RemoveEdge(int a, int b);

  void DFSTransitiveTraversal(std::unordered_set<int> &visited, int current);

  void MergePair(int a, int b);
  void TryMergePair(int a, int b, const StabiliserTableau &tableau);
  void TryCancel(int a, const StabiliserTableau &tableau);
  bool CheckPhase(int a);

  std::vector<int> TopologicalSort() const;

  int nextIndex{};
  std::unordered_map<int, PauliExponential> paulis;
  std::unordered_map<int, std::unordered_set<int>> edges;
  std::unordered_map<int, std::unordered_set<int>> back_edges;
  std::unordered_map<int, std::unordered_map<int, int>> transCount;
  std::unordered_map<int, std::unordered_set<int>> canMerge;
};

}  // namespace circuit
}  // namespace qstabr

#endif
