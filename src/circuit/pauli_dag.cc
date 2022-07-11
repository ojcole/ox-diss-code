#include "pauli_dag.h"

#include <cassert>
#include <thread>

#include "phase/phase.h"
#include "single_qubit_unitary.h"

namespace qstabr {
namespace circuit {

PauliDAG::PauliDAG() {}

void PauliDAG::AddPauli(PauliExponential&& newPauli) {
  int index = nextIndex;
  for (int i{}; i < paulis.size(); i++) {
    if (!newPauli.CommutesWith(paulis.at(i))) {
      AddEdge(index, i);
    }
  }
  edges[index];
  back_edges[index];
  paulis.insert({index, std::move(newPauli)});
  nextIndex++;
}

void PauliDAG::AddEdge(int a, int b) {
  edges[a].insert(b);
  back_edges[b].insert(a);
}

void PauliDAG::RemoveEdge(int a, int b) {
  edges[a].erase(b);
  back_edges[b].erase(a);
}

std::vector<PauliExponential> PauliDAG::GetPaulis() {
  std::vector<PauliExponential> pauliVector;
  auto tsort = TopologicalSort();
  for (auto idx : tsort) {
    pauliVector.push_back(std::move(paulis.at(idx)));
  }

  nextIndex = 0;
  paulis.clear();
  edges.clear();
  back_edges.clear();

  return pauliVector;
}

std::vector<CliffordGate> PauliDAG::PullOutCliffords(
    const QubitManager& qubitManager) {
  auto tsort = TopologicalSort();
  std::vector<CliffordGate> cliffordGates;
  for (size_t i{}; i < tsort.size(); i++) {
    auto idx = tsort[i];
    auto& pauli = paulis.at(idx);
    auto cliffords = pauli.GetCliffordRepresentation(qubitManager);
    if (!cliffords.has_value()) continue;
    RemovePauli(idx);
    cliffordRemovals++;
    for (const auto& clifford : *cliffords) {
      for (size_t j{}; j < i; j++) {
        auto prevIdx = tsort[j];
        if (paulis.find(prevIdx) == paulis.end()) continue;
        auto& prevPauli = paulis.at(prevIdx);
        prevPauli.PushCliffordThrough(clifford, qubitManager);
      }
      cliffordGates.push_back(clifford);
    }
  }
  return cliffordGates;
}

std::vector<CliffordGate> PauliDAG::PullOutPis(
    const QubitManager& qubitManager) {
  auto tsort = TopologicalSort();
  std::vector<CliffordGate> cliffordGates;
  for (size_t i{}; i < tsort.size(); i++) {
    auto idx = tsort[i];
    auto& pauli = paulis.at(idx);
    const auto& string = pauli.GetString();
    auto phaseExpr = pauli.GetExpr().constant_eval();
    if (!phaseExpr.has_value() || !isPi(*phaseExpr)) continue;
    std::vector<int> x_indices;
    std::vector<int> z_indices;
    bool hasY = false;
    for (int j{}; j < string.size(); j++) {
      if (string[j] == Z) z_indices.push_back(j);
      if (string[j] == X) x_indices.push_back(j);
      if (string[j] == Y) {
        hasY = true;
        break;
      }
    }
    if (hasY) continue;

    RemovePauli(idx);

    for (size_t j{}; j < i; j++) {
      auto prevIdx = tsort[j];
      if (paulis.find(prevIdx) == paulis.end()) continue;
      auto& prevPauli = paulis.at(prevIdx);
      for (auto x_index : x_indices) {
        auto clifford = CliffordGate::CreateXRot(
            qubitManager.GetIndexQubit(x_index), phase::RationalPhase(1));
        prevPauli.PushCliffordThrough(clifford, qubitManager);
      }
      for (auto z_index : z_indices) {
        auto clifford = CliffordGate::CreateZRot(
            qubitManager.GetIndexQubit(z_index), phase::RationalPhase(1));
        prevPauli.PushCliffordThrough(clifford, qubitManager);
      }
    }

    for (auto x_index : x_indices) {
      auto clifford = CliffordGate::CreateXRot(
          qubitManager.GetIndexQubit(x_index), phase::RationalPhase(1));
      cliffordGates.push_back(clifford);
    }
    for (auto z_index : z_indices) {
      auto clifford = CliffordGate::CreateZRot(
          qubitManager.GetIndexQubit(z_index), phase::RationalPhase(1));
      cliffordGates.push_back(clifford);
    }
  }
  return cliffordGates;
}

void PauliDAG::DFSTransitiveTraversal(std::unordered_set<int>& visited,
                                      int current) {
  const auto& children = edges[current];
  for (auto child : children) {
    if (visited.find(child) == visited.end()) {
      visited.insert(child);
      DFSTransitiveTraversal(visited, child);
    }
  }
}

bool PauliDAG::DFSCanReach(std::unordered_set<int>& visited, int current,
                           int target) const {
  if (visited.find(current) != visited.end()) return false;

  const auto& children = edges.at(current);
  if (children.find(target) != children.end()) return true;
  visited.insert(current);

  for (auto child : children) {
    if (DFSCanReach(visited, child, target)) return true;
  }

  return false;
}

void PauliDAG::RemovePauli(int a) {
  std::unordered_set<int> children = edges[a];
  std::unordered_set<int> parents = back_edges[a];

  for (auto parent : parents) {
    RemoveEdge(parent, a);
  }

  for (auto child : children) {
    RemoveEdge(a, child);
  }

  paulis.erase(a);

  edges.erase(a);
  back_edges.erase(a);
}

void PauliDAG::MergePair(int a, int b, bool sign) {
  {
    const auto& pauliA = paulis.at(a).GetString();
    const auto& pauliB = paulis.at(b).GetString();

    int aCount{}, bCount{};
    for (size_t i{}; i < pauliA.size(); i++) {
      if (pauliA[i] != I) aCount++;
      if (pauliB[i] != I) bCount++;
    }

    if (aCount > bCount) {
      std::swap(a, b);
    }
  }

  const auto& pauliA = paulis.at(a).GetString();
  const auto& pauliB = paulis.at(b).GetString();

  const auto mergeString = PauliString::StringDifference(pauliA, pauliB);

  int iCount{};

  for (size_t i{}; i < pauliA.size(); i++) {
    if (pauliA[i] == X) {
      if (mergeString[i] == Z) {
        iCount--;
      } else if (mergeString[i] == Y) {
        iCount++;
      }
    } else if (pauliA[i] == Z) {
      if (mergeString[i] == X) {
        iCount--;
        sign = !sign;
      } else if (mergeString[i] == Y) {
        iCount++;
        sign = !sign;
      }
    } else if (pauliA[i] == Y) {
      if (mergeString[i] == Z) {
        iCount++;
      } else if (mergeString[i] == X) {
        iCount++;
        sign = !sign;
      }
    }
  }

  if (std::abs(iCount) % 4 != 0) sign = !sign;

  if (sign) paulis.at(a).Negate();

  if (paulis.at(a).GetString() == paulis.at(b).GetString()) {
    identityMerges++;
  }
  totalMerges++;

  paulis.at(b).CombineWithPauli(paulis.at(a));

  RemovePauli(a);
}

PauliDAG::OptStats PauliDAG::GetStats() const {
  return {
    identityMerges : identityMerges,
    totalMerges : totalMerges,
    phaseRemovals : phaseRemovals,
    cancellations : cancellations,
    cliffordRemovals : cliffordRemovals
  };
}

std::optional<bool> PauliDAG::CanMergePair(
    int a, int b, const StabiliserTableau& tableau) const {
  if (paulis.find(a) == paulis.end() || paulis.find(b) == paulis.end()) {
    return std::nullopt;
  }
  if (edges.at(a).find(b) != edges.at(a).end()) return std::nullopt;
  if (edges.at(b).find(a) != edges.at(b).end()) return std::nullopt;

  const auto& pauliA = paulis.at(a);
  const auto& pauliB = paulis.at(b);

  std::unordered_set<int> set1;
  std::unordered_set<int> set2;

  if (DFSCanReach(set1, a, b) || DFSCanReach(set2, b, a)) return std::nullopt;

  auto mergeString =
      PauliString::StringDifference(pauliA.GetString(), pauliB.GetString());
  auto createSign = tableau.CanCreate(mergeString);

  if (!createSign.has_value()) return std::nullopt;

  for (auto parent : back_edges.at(a)) {
    if (!paulis.at(parent).GetString().CommutesWith(mergeString))
      return std::nullopt;
  }

  for (auto parent : back_edges.at(b)) {
    if (!paulis.at(parent).GetString().CommutesWith(mergeString))
      return std::nullopt;
  }

  return createSign;
}

void PauliDAG::TryMergePair(int a, int b, const StabiliserTableau& tableau) {
  auto createSign = CanMergePair(a, b, tableau);
  if (!createSign.has_value()) return;

  MergePair(a, b, *createSign);
}

void PauliDAG::TryCancel(int a, const StabiliserTableau& tableau) {
  const auto& pauli = paulis.at(a);
  if (back_edges[a].size() > 0) return;
  if (!tableau.CanCreate(pauli.GetString())) return;
  cancellations++;
  RemovePauli(a);
}

bool PauliDAG::CheckPhase(int a) {
  const double pi = 3.14159265358979323846;
  const auto& pauli = paulis.at(a);
  std::optional<double> value = pauli.GetExpr().constant_eval();
  if (value.has_value() && std::abs(std::remainder(*value, 2 * pi)) < 1e-10) {
    phaseRemovals++;
    RemovePauli(a);
    return true;
  }
  return false;
}

void PauliDAG::ExhaustiveRunner(const StabiliserTableau& tableau) {
  size_t size = paulis.size();
  size_t newSize = size;
  do {
    size = newSize;
    auto tsort = TopologicalSort();
    for (auto idx : tsort) {
      for (auto other : tsort) {
        if (paulis.find(idx) == paulis.end()) break;
        if (paulis.find(other) == paulis.end()) continue;
        if (idx == other) continue;
        TryMergePair(other, idx, tableau);
      }
    }
    for (auto idx : tsort) {
      if (paulis.find(idx) == paulis.end()) continue;
      if (CheckPhase(idx)) continue;
      TryCancel(idx, tableau);
    }
    newSize = paulis.size();
  } while (newSize > 0 && newSize < size);
}

void ExhaustiveRunnerParallelWorker(std::shared_ptr<PauliDAG::Config> config,
                                    PauliDAG* dag) {
  const size_t batchSize = 10;
  std::vector<int> indices;
  indices.resize(batchSize);
  const StabiliserTableau& tableau = config->tableau;
  moodycamel::ConcurrentQueue<int>& queue = config->queue;
  const std::vector<int>& tsort = config->tsort;
  size_t count;
  while ((count = queue.try_dequeue_bulk(indices.begin(), batchSize)) != 0) {
    for (size_t i{}; i < count; i++) {
      auto idx = indices[i];
      for (auto other : tsort) {
        if (idx == other) continue;
        if (dag->paulis.find(idx) == dag->paulis.end()) break;
        if (dag->paulis.find(other) == dag->paulis.end()) continue;
        bool sign;
        {
          std::shared_lock lock(dag->rw_lock);
          auto createSign = dag->CanMergePair(other, idx, tableau);
          if (!createSign.has_value()) continue;
          sign = *createSign;
        }
        {
          std::unique_lock lock(dag->rw_lock);
          if (dag->paulis.find(idx) == dag->paulis.end() ||
              dag->paulis.find(other) == dag->paulis.end()) {
            continue;
          }
          dag->MergePair(other, idx, sign);
        }
      }
    }
  }
}

void PauliDAG::ExhaustiveRunnerParallel(const StabiliserTableau& tableau,
                                        int threadCount) {
  size_t size = paulis.size();
  size_t newSize = size;
  do {
    size = newSize;
    std::vector<std::thread> threads;
    threads.reserve(threadCount);
    auto tsort = TopologicalSort();
    moodycamel::ConcurrentQueue<int> queue(tsort.size());
    for (auto idx : tsort) {
      queue.enqueue(idx);
    }
    auto config = std::make_shared<Config>(Config({tableau, queue, tsort}));
    for (int i{}; i < threadCount; i++) {
      std::thread thread(ExhaustiveRunnerParallelWorker, config, this);
      threads.push_back(std::move(thread));
    }
    for (int i{}; i < threadCount; i++) {
      threads[i].join();
    }
    for (auto idx : tsort) {
      if (paulis.find(idx) == paulis.end()) continue;
      if (CheckPhase(idx)) continue;
      TryCancel(idx, tableau);
    }
    newSize = paulis.size();
  } while (newSize > 0 && newSize < size);
}

void PauliDAG::Reduce(const StabiliserTableau& tableau) {
  auto tsort = TopologicalSort();
  for (auto it = tsort.rbegin(); it != tsort.rend(); it++) {
    auto& pauli = paulis.at(*it);
    const auto& strings = pauli.GetString().StringDecomps();
    for (const auto& str : strings) {
      auto canCreate = tableau.CanCreate(str);
      if (!canCreate.has_value()) continue;
      bool canApply = true;
      for (auto parent : back_edges[*it]) {
        if (!paulis.at(parent).GetString().CommutesWith(str)) {
          canApply = false;
          break;
        }
      }
      if (canApply) {
        pauli.ApplyString(str, *canCreate);
      }
    }
  }
}

std::vector<int> PauliDAG::TopologicalSort() const {
  std::vector<int> nodes;
  nodes.resize(paulis.size());
  size_t index = 0;
  for (const auto& pair : paulis) {
    nodes[index++] = pair.first;
  }
  std::sort(nodes.begin(), nodes.end(), std::greater{});
  return nodes;
}

void PauliDAG::Print() const {
  auto tsort = TopologicalSort();
  std::cout << tsort.size() << std::endl;
  for (const auto& pauli : tsort) {
    paulis.at(pauli).Print();
  }
}

size_t PauliDAG::Size() const { return paulis.size(); }

void ResetBlocker(std::vector<PauliLetter>& blockers, int qubit,
                  std::vector<SimpleClifford>& result,
                  std::vector<int>& unitaries,
                  const QubitManager& qubitManager) {
  blockers[qubit] = I;
  int size = result.size();
  result.push_back(SingleQubitUnitary(qubitManager.GetIndexQubit(qubit)));
  if (unitaries[qubit] == qubit) {
    std::get<SingleQubitUnitary>(result[unitaries[qubit]]).ClearAlpha();
  }
  unitaries[qubit] = size;
}

std::vector<SimpleClifford> PauliDAG::SynthesiseCliffords(
    const QubitManager& qubitManager, int numQubits,
    const std::vector<bool>& qubitPis) {
  std::vector<SimpleClifford> result;
  result.reserve(numQubits);
  std::vector<int> unitaries;
  unitaries.reserve(numQubits);
  for (int i{}; i < numQubits; i++) {
    SingleQubitUnitary unitary(qubitManager.GetIndexQubit(i));
    if (qubitPis[i]) {
      unitary.AddXPhase(phase::RationalPhase(1));
    }
    result.push_back(unitary);
    unitaries.push_back(i);
  }

  std::vector<PauliLetter> blockers(numQubits, I);
  auto tsort = TopologicalSort();
  for (auto idx : tsort) {
    const auto& pauli = paulis.at(idx);
    const auto& string = pauli.GetString();
    int z_qubit = -1;
    int x_qubit = -1;
    for (int i{}; i < string.size(); i++) {
      assert(string[i] == Z || string[i] == X || string[i] == I);
      if (string[i] == Z) {
        assert(z_qubit == -1);
        z_qubit = i;
      } else if (string[i] == X) {
        assert(x_qubit == -1);
        x_qubit = i;
      }
    }
    auto phase = phase::GetRationalPhaseFromExpr(pauli.GetExpr());
    if (pauli.IsNegated()) phase *= -1;
    if (z_qubit == -1) {
      assert(x_qubit != -1);
      if (blockers[x_qubit] == Z || blockers[x_qubit] == Y) {
        ResetBlocker(blockers, x_qubit, result, unitaries, qubitManager);
      }
      assert(std::holds_alternative<SingleQubitUnitary>(
          result[unitaries[x_qubit]]));
      std::get<SingleQubitUnitary>(result[unitaries[x_qubit]]).AddXPhase(phase);
    } else if (x_qubit == -1) {
      if (blockers[z_qubit] == X || blockers[z_qubit] == Y) {
        ResetBlocker(blockers, z_qubit, result, unitaries, qubitManager);
      }
      assert(std::holds_alternative<SingleQubitUnitary>(
          result[unitaries[z_qubit]]));
      std::get<SingleQubitUnitary>(result[unitaries[z_qubit]]).AddZPhase(phase);
    } else {
      assert(std::holds_alternative<SingleQubitUnitary>(
          result[unitaries[z_qubit]]));
      assert(std::holds_alternative<SingleQubitUnitary>(
          result[unitaries[x_qubit]]));
      if (blockers[z_qubit] == X || blockers[z_qubit] == Y) {
        ResetBlocker(blockers, z_qubit, result, unitaries, qubitManager);
      }
      if (blockers[x_qubit] == Z || blockers[x_qubit] == Y) {
        ResetBlocker(blockers, x_qubit, result, unitaries, qubitManager);
      }
      std::get<SingleQubitUnitary>(result[unitaries[x_qubit]]).AddXPhase(phase);
      std::get<SingleQubitUnitary>(result[unitaries[z_qubit]]).AddZPhase(phase);
      if (phase != 1) {
        result.push_back(
            CliffordGate::CreateCNOT(qubitManager.GetIndexQubit(z_qubit),
                                     qubitManager.GetIndexQubit(x_qubit)));
        if (blockers[x_qubit] != I && blockers[x_qubit] != X) {
          ResetBlocker(blockers, x_qubit, result, unitaries, qubitManager);
        } else {
          blockers[x_qubit] = X;
        }
        if (blockers[z_qubit] != I && blockers[z_qubit] != Z) {
          ResetBlocker(blockers, z_qubit, result, unitaries, qubitManager);
        } else {
          blockers[z_qubit] = Z;
        }
      }
    }
  }
  for (int i{}; i < numQubits; i++) {
    if (unitaries[i] == i) {
      std::get<SingleQubitUnitary>(result[unitaries[i]]).ClearAlpha();
    }
  }
  return result;
}

void PauliDAG::Synthesise(std::vector<SimpleGate>& gates,
                          const QubitManager& qubitManager) {
  auto tsort = TopologicalSort();
  for (const auto& pauli : tsort) {
    paulis.at(pauli).Synthesise(gates, qubitManager);
  }
}

}  // namespace circuit
}  // namespace qstabr
