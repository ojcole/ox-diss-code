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

std::vector<CliffordGate> PauliDAG::PullOutCliffords(
    const QubitManager& qubitManager) {
  auto tsort = TopologicalSort();
  std::vector<CliffordGate> cliffordGates;
  for (size_t i{}; i < tsort.size(); i++) {
    auto idx = tsort[i];
    auto& pauli = paulis.at(idx);
    auto cliffords = pauli.GetCliffordRepresentation(qubitManager);
    if (!cliffords.has_value()) continue;
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
    RemovePauli(idx);
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
    for (size_t j{}; j < i; j++) {
      auto prevIdx = tsort[j];
      if (paulis.find(prevIdx) == paulis.end()) continue;
      auto& prevPauli = paulis.at(prevIdx);
      for (auto x_index : x_indices) {
        auto clifford =
            CliffordGate::CreateXRot(x_index, phase::RationalPhase(1));
        prevPauli.PushCliffordThrough(clifford, qubitManager);
      }
      for (auto z_index : z_indices) {
        auto clifford =
            CliffordGate::CreateZRot(z_index, phase::RationalPhase(1));
        prevPauli.PushCliffordThrough(clifford, qubitManager);
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
    cliffordRemovals : cliffordRemovals
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
                  std::vector<int>& unitaries,
                  const QubitManager& qubitManager) {
  blockers[qubit] = I;
  int size = result.size();
  result.push_back(SingleQubitUnitary(qubit));
  if (unitaries[qubit] == qubit) {
    std::get<SingleQubitUnitary>(result[unitaries[qubit]]).ClearAlpha();
  }
  unitaries[qubit] = size;
}

std::vector<SimpleClifford> PauliDAG::SynthesiseCliffords(
    const QubitManager& qubitManager, const std::vector<bool>& qubitPis) const {
  int numQubits = qubitManager.GetNumQubits();
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
        result.push_back(CliffordGate::CreateCNOT(z_qubit, x_qubit));
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
  auto groupings = SimpleGroupings();
  for (auto& group : groupings) {
    auto cliffords = DiagonaliseGroup(group, qubitManager);
    for (const auto& clifford : cliffords) {
      gates.push_back(clifford);
    }
    // REPLACE WITH GRAY SYNTH
    for (const auto pauliIndex : group) {
      paulis.at(pauliIndex).Synthesise(gates, qubitManager);
    }
    for (auto it = cliffords.rbegin(); it != cliffords.rend(); it++) {
      gates.push_back(it->Dagger());
    }
  }
}

namespace {

CliffordGate GetConj(PauliLetter letter, int qubit) {
  assert(letter != I && letter != Z);
  if (letter == X) {
    return CliffordGate::CreateHAD(qubit);
  }
  assert(letter == Y);
  return CliffordGate::CreateXRot(qubit, phase::PI_BY_2);
}

}  // namespace

void PauliDAG::DiagonaliseTrivial(std::vector<int>& group,
                                  const QubitManager& qubitManager,
                                  std::list<int>& qubits,
                                  std::vector<CliffordGate>& conj) {
  int numQubits = qubitManager.GetNumQubits();
  for (int i{}; i < numQubits; i++) {
    PauliLetter letter = I;
    for (auto pauliIndex : group) {
      const auto& pauliString = paulis.at(pauliIndex).GetString();
      if (pauliString[i] != letter) {
        if (letter != I) {
          letter = I;
          break;
        } else {
          letter = pauliString[i];
        }
      }
    }
    if (letter != Z && letter != I) {
      for (auto pauliIndex : group) {
        paulis.at(pauliIndex).DiagonaliseQubit(i);
      }
      conj.push_back(GetConj(letter, i));
    }
  }
}

// A pair of qubits i,j is compatible iff there exists {A, B} s.t.
//  for all gadgets l,
//      gadget l on qubit i \in {I, A} iff gadget l on qubit j \in {I, B}

// const std::unordered_map<PauliLetter, PauliLetter>
// DIAG_BY_CNOT{{I, Z}, {X, Y}, {Y, X}, {Z, {I, Z}}};

int PauliDAG::NonDiagonalQubits(std::vector<int>& group,
                                const QubitManager& qubitManager) {
  int nonDiagonal = 0;
  int numQubits = qubitManager.GetNumQubits();
  for (int i{}; i < numQubits; i++) {
    for (const auto pauliIndex : group) {
      if (!paulis.at(pauliIndex).DiagAtQubit(i)) {
        nonDiagonal++;
        break;
      }
    }
  }
  return nonDiagonal;
}

void PauliDAG::ConjugateForDiag(std::vector<int>& group,
                                const QubitManager& qubitManager, int qubit,
                                PauliLetter letter,
                                std::vector<CliffordGate>& conj) {
  if (letter != X && letter != Y) return;
  auto gate = letter == X ? CliffordGate::CreateHAD(qubit)
                          : CliffordGate::CreateXRot(qubit, phase::PI_BY_2);
  for (const auto pauliIndex : group) {
    paulis.at(pauliIndex).PushCliffordThrough(gate, qubitManager);
  }
  conj.push_back(std::move(gate));
}

bool PauliDAG::DiagonaliseCompatible(std::vector<int>& group,
                                     const QubitManager& qubitManager,
                                     std::list<int>& qubits,
                                     std::vector<CliffordGate>& conj) {
  int numQubits = qubitManager.GetNumQubits();
  for (auto first_letter : ACTIVE_LETTERS) {
    for (auto second_letter : ACTIVE_LETTERS) {
      for (auto it = qubits.begin(); it != qubits.end(); it++) {
        int i = *it;
        for (int j{i + 1}; j < numQubits; j++) {
          bool all = true;
          int qubit1Count{};
          int qubit2Count{};
          bool qubit1Diag = true;
          bool qubit2Diag = true;
          for (const auto pauliIndex : group) {
            const auto& pauliString = paulis.at(pauliIndex).GetString();
            auto i_let = pauliString[i];
            auto j_let = pauliString[j];

            if (i_let != I && i_let != Z) qubit1Diag = false;
            if (i_let != I) qubit1Count++;

            if (j_let != I && j_let != Z) qubit2Diag = false;
            if (j_let != I) qubit2Count++;

            if ((i_let == first_letter || i_let == I) !=
                (j_let == second_letter || j_let == I)) {
              all = false;
              break;
            }
          }
          if (qubit1Diag && qubit2Diag) continue;
          if (all) {
            int control = i;
            int target = j;
            if (qubit2Diag || qubit1Count < qubit2Count) {
              std::swap(control, target);
            }
            ConjugateForDiag(group, qubitManager, i, first_letter, conj);
            ConjugateForDiag(group, qubitManager, j, second_letter, conj);
            auto gate = CliffordGate::CreateCNOT(control, target);
            for (const auto pauliIndex : group) {
              paulis.at(pauliIndex).PushCliffordThrough(gate, qubitManager);
            }
            conj.push_back(std::move(gate));
            return true;
          }
        }
      }
    }
  }
  return false;
}

void PauliDAG::DiagonaliseMinWeight(std::vector<int>& group,
                                    const QubitManager& qubitManager,
                                    std::list<int>& qubits,
                                    std::vector<CliffordGate>& conj) {
  int weight = qubitManager.GetNumQubits() + 1;
  int minPauli = -1;
  for (const auto pauliIndex : group) {
    int currentWeight = paulis.at(pauliIndex).GetString().Weight().size();
    if (currentWeight < weight) {
      weight = currentWeight;
      minPauli = pauliIndex;
    }
  }
  assert(minPauli != -1);
  std::vector<SimpleGate> gates;
  auto& pauli = paulis.at(minPauli);
  pauli.Synthesise(gates, qubitManager);
  for (size_t i{}; i < gates.size() / 2; i++) {
    assert(std::holds_alternative<CliffordGate>(gates[i]));
    auto& gate = std::get<CliffordGate>(gates[i]);
    for (const auto pauliIndex : group) {
      if (pauliIndex == minPauli) continue;
      paulis.at(pauliIndex).PushCliffordThrough(gate, qubitManager);
    }
    conj.push_back(std::move(gate));
  }
  assert(std::holds_alternative<ZGate>(gates[gates.size() / 2]));
  auto gate = std::get<ZGate>(gates[gates.size() / 2]);
  int remainingQubit = gate.GetQubit();
  pauli.ReduceToZ(remainingQubit);
}

std::vector<CliffordGate> PauliDAG::DiagonaliseGroup(
    std::vector<int>& group, const QubitManager& qubitManager) {
  std::list<int> qubits;
  int numQubits = qubitManager.GetNumQubits();
  for (int i{}; i < numQubits; i++) {
    for (const auto pauliIndex : group) {
      if (!paulis.at(pauliIndex).DiagAtQubit(i)) {
        qubits.push_back(i);
      }
    }
  }

  std::vector<CliffordGate> conj;
  while (!qubits.empty()) {
    DiagonaliseTrivial(group, qubitManager, qubits, conj);
    if (DiagonaliseCompatible(group, qubitManager, qubits, conj)) continue;
    DiagonaliseMinWeight(group, qubitManager, qubits, conj);
  }
  return conj;
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
