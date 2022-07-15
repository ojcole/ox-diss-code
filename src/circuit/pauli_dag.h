#ifndef CIRCUIT_PAULI_DAG_H_
#define CIRCUIT_PAULI_DAG_H_

#include <shared_mutex>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

#include "helpers.h"
#include "moodycamel/concurrentqueue.h"
#include "pauli_exponential.h"
#include "stabiliser_tableau.h"

namespace qstabr {
namespace circuit {

class PauliDAG {
 public:
  PauliDAG();

  void AddPauli(PauliExponential &&pauli);

  void ExhaustiveRunner(const StabiliserTableau &tableau);
  void ExhaustiveRunnerParallel(const StabiliserTableau &tableau, int threads);

  void Print() const;

  size_t Size() const;

  void Synthesise(std::vector<SimpleGate> &gates,
                  const QubitManager &qubitManager);

  std::vector<SimpleClifford> SynthesiseCliffords(
      const QubitManager &qubitManager, int numQubits,
      const std::vector<bool> &qubitPis);

  struct OptStats {
    int identityMerges;
    int totalMerges;
    int phaseRemovals;
    int cancellations;
    int cliffordRemovals;
  };

  OptStats GetStats() const;

  std::vector<CliffordGate> PullOutCliffords(const QubitManager &qubitManager);
  std::vector<CliffordGate> PullOutPis(const QubitManager &qubitManager);

  // Destructive
  std::vector<PauliExponential> GetPaulis();

 private:
  struct Config {
    const StabiliserTableau &tableau;
    moodycamel::ConcurrentQueue<int> &queue;
    const std::vector<int> &tsort;
  };

  void AddEdge(int a, int b);
  void RemoveEdge(int a, int b);

  void DFSTransitiveTraversal(std::unordered_set<int> &visited, int current);
  bool DFSCanReach(std::unordered_set<int> &visited, int current,
                   int target) const;
  bool StringCommutesParents(int a, int b) const;

  void MergePair(int a, int b, bool sign);
  void TryMergePair(int a, int b, const StabiliserTableau &tableau);
  std::optional<bool> CanMergePair(int a, int b,
                                   const StabiliserTableau &tableau) const;
  void TryCancel(int a, const StabiliserTableau &tableau);
  bool CheckPhase(int a);

  void RemovePauli(int a);

  std::vector<int> TopologicalSort() const;

  friend void ExhaustiveRunnerParallelWorker(std::shared_ptr<Config> config,
                                             PauliDAG *dag);

  int nextIndex{};
  std::unordered_map<int, PauliExponential> paulis;
  std::unordered_map<int, std::unordered_set<int>> edges;
  std::unordered_map<int, std::unordered_set<int>> back_edges;

  std::shared_mutex rw_lock;

  int identityMerges{};
  int totalMerges{};
  int phaseRemovals{};
  int cliffordRemovals{};
  int cancellations{};
};

}  // namespace circuit
}  // namespace qstabr

#endif
