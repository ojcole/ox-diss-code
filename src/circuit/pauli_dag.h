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
  PauliDAG(int numQubits);

  void AddPauli(PauliExponential &&pauli);

  void ExhaustiveRunner(const StabiliserTableau &tableau);
  void ExhaustiveRunnerParallel(const StabiliserTableau &tableau, int threads);

  void Print() const;

  size_t Size() const;

  void Synthesise(std::vector<SimpleGate> &gates,
                  std::vector<PauliString> stabilisers = {},
                  const SynthOptions &options = {});

  std::vector<SimpleClifford> SynthesiseCliffords(
      const std::vector<bool> &qubitPis) const;

  struct OptStats {
    int identityMerges;
    int totalMerges;
    int phaseRemovals;
    int cancellations;
    int cliffordRemovals;
    double stringReductions;
  };

  OptStats GetStats() const;

  std::vector<CliffordGate> PullOutCliffords();
  std::vector<CliffordGate> PullOutPis();

  // Destructive
  std::vector<PauliExponential> GetPaulis();

 private:
  void ReduceGroup(std::vector<int> &group,
                   std::vector<PauliString> &stabilisers);
  std::vector<std::vector<int>> SimpleGroupings();

  void AddEdge(int a, int b);
  void RemoveEdge(int a, int b);

  bool StringCommutesParents(int a, int b) const;

  void MergePair(int a, int b, bool sign);
  bool TryMergePair(int a, int b, const StabiliserTableau &tableau);
  std::optional<bool> CanMergePair(int a, int b,
                                   const StabiliserTableau &tableau) const;
  bool TryCancel(int a, const StabiliserTableau &tableau);
  bool CheckPhase(int a);

  void RemovePauli(int a);

  std::vector<int> TopologicalSort() const;

  struct Config {
    const StabiliserTableau &tableau;
    moodycamel::ConcurrentQueue<size_t> &queue;
    const std::vector<int> &tsort;
  };
  struct Merge {
    int pauli1;
    int pauli2;
    bool sign;
  };
  using MergeVec = std::vector<Merge>;
  friend void ExhaustiveRunnerParallelWorker(std::shared_ptr<Config> config,
                                             std::shared_ptr<MergeVec> merges,
                                             PauliDAG *dag);
  int NonDiagonalQubits(std::vector<int> &group);
  void ConjugateForDiag(std::vector<int> &group, int qubit, PauliLetter letter,
                        std::vector<CliffordGate> &conj);
  void DiagonaliseTrivial(std::vector<int> &group, std::list<int> &qubits,
                          std::vector<CliffordGate> &conj);
  bool DiagonaliseCompatibleCheck(std::vector<int> &group,
                                  std::list<int> &qubits,
                                  std::vector<CliffordGate> &conj);
  bool DiagonaliseCompatible(std::vector<int> &group, std::list<int> &qubits,
                             std::vector<CliffordGate> &conj);
  void DiagonaliseMinWeight(std::vector<int> &group, std::list<int> &qubits,
                            std::vector<CliffordGate> &conj);
  std::vector<CliffordGate> DiagonaliseGroup(std::vector<int> &group);

  int numQubits;

  int nextIndex{};
  std::unordered_map<int, PauliExponential> paulis;
  std::unordered_map<int, std::unordered_set<int>> back_edges;

  std::shared_mutex rw_lock;

  int identityMerges{};
  int totalMerges{};
  int phaseRemovals{};
  int cliffordRemovals{};
  int cancellations{};
  double stringReductions{};
};

}  // namespace circuit
}  // namespace qstabr

#endif
