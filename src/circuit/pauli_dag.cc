#include "pauli_dag.h"

#include <cassert>
#include <random>
#include <thread>

#include "diagonaliser.h"
#include "gray_synther.h"
#include "phase/phase.h"
#include "single_qubit_unitary.h"

namespace qstabr {
namespace circuit {

PauliDAG::PauliDAG(int numQubits) : numQubits(numQubits) {}

void PauliDAG::AddPauli(PauliExponential&& newPauli) {
  int index = nextIndex;
  for (const auto& pair : paulis) {
    if (!newPauli.CommutesWith(pair.second)) {
      AddEdge(index, pair.first);
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

std::vector<CliffordGate> PauliDAG::PullOutCliffords() {
  auto tsort = TopologicalSort();
  std::vector<CliffordGate> cliffordGates;
  for (size_t i{}; i < tsort.size(); i++) {
    auto idx = tsort[i];
    auto& pauli = paulis.at(idx);
    auto cliffords = pauli.GetCliffordRepresentation();
    if (!cliffords.has_value()) continue;
    cliffordRemovals++;
    for (const auto& clifford : *cliffords) {
      for (size_t j{}; j < i; j++) {
        auto prevIdx = tsort[j];
        if (paulis.find(prevIdx) == paulis.end()) continue;
        auto& prevPauli = paulis.at(prevIdx);
        prevPauli.PushCliffordThrough(clifford);
      }
      cliffordGates.push_back(clifford);
    }
    RemovePauli(idx);
  }
  return cliffordGates;
}

std::vector<CliffordGate> PauliDAG::PullOutPis() {
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
    for (size_t j{}; j < i; j++) {
      auto prevIdx = tsort[j];
      if (paulis.find(prevIdx) == paulis.end()) continue;
      auto& prevPauli = paulis.at(prevIdx);
      for (auto x_index : x_indices) {
        auto clifford =
            CliffordGate::CreateXRot(x_index, phase::RationalPhase(1));
        prevPauli.PushCliffordThrough(clifford);
      }
      for (auto z_index : z_indices) {
        auto clifford =
            CliffordGate::CreateZRot(z_index, phase::RationalPhase(1));
        prevPauli.PushCliffordThrough(clifford);
      }
    }

    for (auto x_index : x_indices) {
      auto clifford =
          CliffordGate::CreateXRot(x_index, phase::RationalPhase(1));
      cliffordGates.push_back(clifford);
    }
    for (auto z_index : z_indices) {
      auto clifford =
          CliffordGate::CreateZRot(z_index, phase::RationalPhase(1));
      cliffordGates.push_back(clifford);
    }
    RemovePauli(idx);
  }
  return cliffordGates;
}

bool PauliDAG::StringCommutesParents(int a, int b) const {
  return back_edges.at(a) == back_edges.at(b);
}

void PauliDAG::RemovePauli(int a) {
  RemovePauliEdges(a);

  paulis.erase(a);
  edges.erase(a);
  back_edges.erase(a);
}

void PauliDAG::RemovePauliEdges(int a) {
  std::unordered_set<int> children = edges[a];
  std::unordered_set<int> parents = back_edges[a];

  for (auto parent : parents) {
    RemoveEdge(parent, a);
  }

  for (auto child : children) {
    RemoveEdge(a, child);
  }
}

void PauliDAG::MergePair(int a, int b, bool sign) {
  {
    const auto& pauliA = paulis.at(a).GetString();
    const auto& pauliB = paulis.at(b).GetString();

    int aCount{}, bCount{};
    for (int i{}; i < pauliA.size(); i++) {
      if (pauliA[i] != I) aCount++;
      if (pauliB[i] != I) bCount++;
    }

    if (aCount > bCount) {
      std::swap(a, b);
    }
  }

  const auto& pauliA = paulis.at(a).GetString();
  const auto& pauliB = paulis.at(b).GetString();

  bool mergeSign = PauliString::StringMultiplySign(pauliA, pauliB);
  if (mergeSign) sign = !sign;

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
    cliffordRemovals : cliffordRemovals,
    stringReductions : stringReductions
  };
}

std::optional<bool> PauliDAG::CanMergePair(
    int a, int b, const StabiliserTableau& tableau) const {
  if (paulis.find(a) == paulis.end() || paulis.find(b) == paulis.end()) {
    return std::nullopt;
  }

  if (!StringCommutesParents(a, b)) return std::nullopt;

  const auto& pauliA = paulis.at(a);
  const auto& pauliB = paulis.at(b);

  auto mergeString =
      PauliString::StringDifference(pauliA.GetString(), pauliB.GetString());

  return tableau.CanCreate(mergeString);
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
                                    std::shared_ptr<PauliDAG::MergeVec> merges,
                                    PauliDAG* dag) {
  const StabiliserTableau& tableau = config->tableau;
  moodycamel::ConcurrentQueue<size_t>& queue = config->queue;
  const std::vector<int>& tsort = config->tsort;

  std::unordered_set<size_t> merged;

  const size_t batchSize = 20;
  std::vector<size_t> indices;
  indices.resize(batchSize);
  size_t count;

  while ((count = queue.try_dequeue_bulk(indices.begin(), batchSize)) != 0) {
    for (size_t i{}; i < count; i++) {
      size_t index = indices[i];
      if (merged.find(index) != merged.end()) continue;
      auto idx = tsort[index];
      for (size_t j = index + 1; j < tsort.size(); j++) {
        int other = tsort[j];
        bool sign;
        auto createSign = dag->CanMergePair(other, idx, tableau);
        if (!createSign.has_value()) continue;
        sign = *createSign;
        merges->push_back({pauli1 : other, pauli2 : idx, sign : sign});
        merged.insert(j);
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
    moodycamel::ConcurrentQueue<size_t> queue(tsort.size());
    for (size_t i{}; i < tsort.size(); i++) {
      queue.enqueue(i);
    }
    std::vector<std::shared_ptr<MergeVec>> allMerges;
    auto config = std::make_shared<Config>(Config({tableau, queue, tsort}));
    for (int i{}; i < threadCount; i++) {
      auto merges = std::make_shared<MergeVec>();
      allMerges.push_back(merges);
      std::thread thread(ExhaustiveRunnerParallelWorker, config, merges, this);
      threads.push_back(std::move(thread));
    }
    for (int i{}; i < threadCount; i++) {
      threads[i].join();
    }
    for (int i{}; i < threadCount; i++) {
      const auto& merges = *allMerges[i];
      for (const auto& merge : merges) {
        if (paulis.find(merge.pauli1) == paulis.end() ||
            paulis.find(merge.pauli2) == paulis.end()) {
          continue;
        }
        MergePair(merge.pauli1, merge.pauli2, merge.sign);
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
                  std::vector<int>& unitaries) {
  blockers[qubit] = I;
  int size = result.size();
  result.push_back(SingleQubitUnitary(qubit));
  if (unitaries[qubit] == qubit) {
    std::get<SingleQubitUnitary>(result[unitaries[qubit]]).ClearAlpha();
  }
  unitaries[qubit] = size;
}

std::vector<SimpleClifford> PauliDAG::SynthesiseCliffords(
    const std::vector<bool>& qubitPis) const {
  std::vector<SimpleClifford> result;
  result.reserve(numQubits);
  std::vector<int> unitaries;
  unitaries.reserve(numQubits);
  for (int i{}; i < numQubits; i++) {
    SingleQubitUnitary unitary(i);
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
        ResetBlocker(blockers, x_qubit, result, unitaries);
      }
      assert(std::holds_alternative<SingleQubitUnitary>(
          result[unitaries[x_qubit]]));
      std::get<SingleQubitUnitary>(result[unitaries[x_qubit]]).AddXPhase(phase);
    } else if (x_qubit == -1) {
      if (blockers[z_qubit] == X || blockers[z_qubit] == Y) {
        ResetBlocker(blockers, z_qubit, result, unitaries);
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
        ResetBlocker(blockers, z_qubit, result, unitaries);
      }
      if (blockers[x_qubit] == Z || blockers[x_qubit] == Y) {
        ResetBlocker(blockers, x_qubit, result, unitaries);
      }
      std::get<SingleQubitUnitary>(result[unitaries[x_qubit]]).AddXPhase(phase);
      std::get<SingleQubitUnitary>(result[unitaries[z_qubit]]).AddZPhase(phase);
      if (phase != 1) {
        result.push_back(CliffordGate::CreateCNOT(z_qubit, x_qubit));
        if (blockers[x_qubit] != I && blockers[x_qubit] != X) {
          ResetBlocker(blockers, x_qubit, result, unitaries);
        } else {
          blockers[x_qubit] = X;
        }
        if (blockers[z_qubit] != I && blockers[z_qubit] != Z) {
          ResetBlocker(blockers, z_qubit, result, unitaries);
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
                          std::vector<PauliString> stabilisers) {
  auto groupings = SimpleGroupings();
  Diagonaliser diagonaliser(paulis, numQubits);
  GraySynther graySynther(paulis, numQubits);
  for (auto& group : groupings) {
    ReduceGroup(group, stabilisers);
    auto cliffords = diagonaliser.Diagonalise(group);
    for (const auto& clifford : cliffords) {
      gates.push_back(clifford);
    }
    graySynther.GraySynth(gates, group);
    for (auto it = cliffords.rbegin(); it != cliffords.rend(); it++) {
      gates.push_back(it->Dagger());
    }
  }
}

void PauliDAG::ReduceGroup(std::vector<int>& group,
                           std::vector<PauliString>& stabilisers) {
  if (stabilisers.size() == 0) return;

  // Reduce stabilisers to only those that commute with all of group
  for (const auto pauliIndex : group) {
    std::vector<size_t> antiCommutingStabilisers;
    const auto& pauliString = paulis.at(pauliIndex).GetString();
    for (size_t i{}; i < stabilisers.size(); i++) {
      if (!stabilisers[i].CommutesWith(pauliString)) {
        antiCommutingStabilisers.push_back(i);
      }
    }
    if (antiCommutingStabilisers.size() == 0) continue;
    for (size_t i{1}; i < antiCommutingStabilisers.size(); i++) {
      stabilisers[antiCommutingStabilisers[i]] *=
          stabilisers[antiCommutingStabilisers[0]];
    }
    std::swap(stabilisers[antiCommutingStabilisers[0]],
              stabilisers[stabilisers.size() - 1]);
    stabilisers.pop_back();
    if (stabilisers.size() == 0) return;
  }

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<size_t> distribution(0, stabilisers.size() - 1);

  for (const auto pauliIndex : group) {
    auto& pauli = paulis.at(pauliIndex);
    const auto& pauliString = pauli.GetString();
    int currentSize = 0;
    int newSize = pauliString.Weight().size();
    int currentZSize = 0;
    int newZSize = pauliString.NonZWeight();
    while (currentSize != newSize || currentZSize != newZSize) {
      currentSize = newSize;
      currentZSize = newZSize;
      for (size_t j{1}; j <= (stabilisers.size() + 1) / 2; j++) {
        for (size_t i{}; i < std::max(2 * stabilisers.size(), 20UL); i++) {
          auto initialString = stabilisers[distribution(rng)];
          for (size_t k{1}; k < j; k++) {
            initialString *= stabilisers[distribution(rng)];
          }
          pauli.ApplyPauliStabiliser(initialString);
          size_t newWeight = pauliString.Weight().size();
          size_t newNonZWeight = pauliString.NonZWeight();
          if (newWeight < newSize ||
              (newWeight == newSize && newNonZWeight < newZSize)) {
            newSize = newWeight;
            newZSize = newNonZWeight;
            stringReductions++;
          } else {
            pauli.ApplyPauliStabiliser(initialString);
          }
        }
      }
    }
  }
}

std::vector<std::vector<int>> PauliDAG::SimpleGroupings() {
  std::list<int> remaining;
  for (const auto& pauli : paulis) {
    remaining.push_back(pauli.first);
  }

  std::vector<std::vector<int>> result;
  while (!remaining.empty()) {
    std::vector<std::list<int>::iterator> currentGroup;
    for (auto it = remaining.begin(); it != remaining.end(); it++) {
      if (back_edges.at(*it).size() == 0) {
        currentGroup.push_back(it);
      }
    }
    std::vector<int> group;
    for (auto& it : currentGroup) {
      RemovePauliEdges(*it);
      group.push_back(*it);
      remaining.erase(it);
    }
    result.push_back(std::move(group));
  }

  return result;
}

}  // namespace circuit
}  // namespace qstabr
