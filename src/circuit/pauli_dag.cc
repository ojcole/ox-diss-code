#include "pauli_dag.h"

namespace qstabr {
namespace circuit {

PauliDAG::PauliDAG() {}

void PauliDAG::AddPauli(PauliExponential &&newPauli) {
  int index = paulis.size();
  for (int i{}; i < paulis.size(); i++) {
    if (!newPauli.CommutesWith(paulis[i])) {
      edges[i].push_back(index);
    }
  }
  paulis.push_back(std::move(newPauli));
}

std::vector<std::vector<PauliExponential>> PauliDAG::GetGroups() {
  std::vector<std::vector<PauliExponential>> groups;
  std::set<int> grouped;

  while (grouped.size() < paulis.size()) {
    std::vector<PauliExponential> group;
    std::vector<int> indexGroup;
    for (int i{}; i < paulis.size(); i++) {
      bool all = true;
      for (const int index : edges[i]) {
        if (grouped.find(index) == grouped.end()) {
          all = false;
          break;
        }
      }

      if (all) {
        group.push_back(std::move(paulis[i]));
        indexGroup.push_back(i);
      }
    }
    for (int index : indexGroup) {
      grouped.insert(index);
    }
    groups.push_back(std::move(group));
  }

  return groups;
}

}  // namespace circuit
}  // namespace qstabr