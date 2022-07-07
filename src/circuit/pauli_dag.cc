#include "pauli_dag.h"

#include <cassert>

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
                           int target) {
  if (visited.find(current) != visited.end()) return false;

  const auto& children = edges[current];
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
}

void PauliDAG::MergePair(int a, int b, bool sign) {
  if (sign) paulis.at(a).Negate();

  paulis.at(b).CombineWithPauli(paulis.at(a));

  RemovePauli(a);
}

void PauliDAG::TryMergePair(int a, int b, const StabiliserTableau& tableau) {
  if (edges[a].find(b) != edges[a].end()) return;
  if (edges[b].find(a) != edges[b].end()) return;

  const auto& pauliA = paulis.at(a);
  const auto& pauliB = paulis.at(b);

  std::unordered_set<int> set1;
  std::unordered_set<int> set2;

  if (DFSCanReach(set1, a, b) || DFSCanReach(set2, b, a)) return;

  auto mergeString =
      PauliString::StringDifference(pauliA.GetString(), pauliB.GetString());
  auto createSign = tableau.CanCreate(mergeString);

  if (!createSign.has_value()) return;

  for (auto parent : back_edges[a]) {
    if (!paulis.at(parent).GetString().CommutesWith(mergeString)) return;
  }

  for (auto parent : back_edges[b]) {
    if (!paulis.at(parent).GetString().CommutesWith(mergeString)) return;
  }

  MergePair(a, b, *createSign);
}

void PauliDAG::TryCancel(int a, const StabiliserTableau& tableau) {
  const auto& pauli = paulis.at(a);
  if (back_edges[a].size() > 0) return;
  if (!tableau.CanCreate(pauli.GetString())) return;

  RemovePauli(a);
}

bool PauliDAG::CheckPhase(int a) {
  const double pi = 3.14159265358979323846;
  const auto& pauli = paulis.at(a);
  std::optional<double> value = pauli.GetExpr().constant_eval();
  if (value.has_value() && std::abs(std::remainder(*value, 2 * pi)) < 1e-10) {
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
      if (paulis.find(idx) == paulis.end()) continue;
      for (auto other : tsort) {
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
    const QubitManager& qubitManager, int numQubits) {
  std::vector<SimpleClifford> result;
  result.reserve(numQubits);
  std::vector<int> unitaries;
  unitaries.reserve(numQubits);
  for (int i{}; i < numQubits; i++) {
    result.push_back(SingleQubitUnitary(qubitManager.GetIndexQubit(i)));
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
