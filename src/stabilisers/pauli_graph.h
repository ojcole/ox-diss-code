#ifndef STABILISERS_PAULI_GRAPH_H_
#define STABILISERS_PAULI_GRAPH_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pauli.h"

namespace qstabr {
namespace stabilisers {

class PauliGraph {
 public:
  PauliGraph();
  PauliGraph(const std::vector<PauliString> &strings);

  void AddString(const PauliString &string);

 private:
  std::unordered_map<PauliString, std::vector<PauliString>, PauliStringHash>
      edges;
  std::vector<PauliString> strings;
};

}  // namespace stabilisers
}  // namespace qstabr

#endif