#include "pauli_dag.h"

#include "phase/phase.h"

namespace qstabr {
namespace circuit {

PauliDAG::PauliDAG() {}

void PauliDAG::AddPauli(PauliExponential&& newPauli) {
  int index = nextIndex;
  for (const auto& item : paulis) {
    canMerge[index].insert(item.first);
  }
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
  for (const auto& edge : edges[b]) {
    int count = transCount[a][edge]++;
    if (count == 0) {
      canMerge[a].erase(edge);
    }
  }
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
    for (auto child : children) {
      int count = --transCount[parent][child];
      if (count == 0) {
        canMerge[parent].insert(child);
      }
    }
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
  const auto& pauli = paulis.at(a);
  std::optional<double> value = pauli.GetExpr().constant_eval();
  if (value == 0) {
    RemovePauli(a);
    return true;
  }
  return false;
}

void PauliDAG::Runner(const StabiliserTableau& tableau) {
  auto tsort = TopologicalSort();

  for (auto idx : tsort) {
    if (paulis.find(idx) == paulis.end()) continue;
    auto mergeable = canMerge[idx];
    for (auto next : mergeable) {
      if (paulis.find(next) == paulis.end()) continue;
      TryMergePair(next, idx, tableau);
    }
  }

  for (auto idx : tsort) {
    if (paulis.find(idx) == paulis.end()) continue;
    // if (CheckPhase(idx)) continue;
    TryCancel(idx, tableau);
  }
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
    std::cout << "iteration" << std::endl;
  } while (size > 0 && size < newSize);
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

void PauliDAG::Synthesise(std::ostream& output,
                          const QubitManager& qubitManager) {
  auto tsort = TopologicalSort();
  for (const auto& pauli : tsort) {
    paulis.at(pauli).Synthesise(output, qubitManager);
  }
}

}  // namespace circuit
}  // namespace qstabr
