#include "pauli_graph.h"

namespace qstabr {
namespace circuit {

PauliGraph::PauliGraph() {}

PauliGraph::PauliGraph(const std::vector<PauliString> &strings)
    : strings(strings) {
  for (const auto &string : strings) {
    AddString(string);
  }
}

void PauliGraph::AddString(const PauliString &string) {
  auto it = edges.find(string);
  if (it != edges.end()) return;
  std::vector<PauliString> commutingSet;
  for (const auto &str : strings) {
    if (string.DoesCommute(str)) {
      edges[str].push_back(string);
      commutingSet.push_back(str);
    }
  }
  edges[string] = commutingSet;
}

}  // namespace circuit
}  // namespace qstabr