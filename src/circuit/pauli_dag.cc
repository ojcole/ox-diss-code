#include "pauli_dag.h"

namespace qstabr {
namespace circuit {

void PauliDAG::AddPauli(const PauliExponential &newPauli) {
  int index = paulis.size();
  for (int i{}; i < paulis.size(); i++) {
    if (!newPauli.CommutesWith(paulis[i])) {
      edges[i].push_back(index);
    }
  }
  paulis.push_back(newPauli);
}

std::vector<std::vector<const PauliExponential &>> PauliDAG::GetGroups() {
  std::vector<std::vector<const PauliExponential &>> groups;
  std::set<int> grouped;

  while (grouped.size() < paulis.size()) {
    std::vector<const PauliExponential &> group;
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
        group.push_back(paulis[i]);
        indexGroup.push_back(i);
      }
    }
    for (int index : indexGroup) {
      grouped.insert(index);
    }
    groups.push_back(group);
  }

  return groups;
}

}  // namespace circuit
}  // namespace qstabr