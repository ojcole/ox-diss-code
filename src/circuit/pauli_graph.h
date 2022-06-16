#ifndef CIRCUIT_PAULI_GRAPH_H_
#define CIRCUIT_PAULI_GRAPH_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pauli.h"

namespace qstabr {
namespace circuit {

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

}  // namespace circuit
}  // namespace qstabr

#endif