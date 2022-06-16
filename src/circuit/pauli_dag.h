#ifndef CIRCUIT_PAULI_DAG_H_
#define CIRCUIT_PAULI_DAG_H_

#include <unordered_map>
#include <vector>

#include "pauli.h"

namespace qstabr {
namespace circuit {

class PauliDAG {
 public:
  PauliDAG();

  void AddPauli(const PauliExponential &pauli);

  std::vector<std::vector<const PauliExponential &>> GetGroups();

 private:
  std::vector<PauliExponential> paulis;
  std::unordered_map<int, std::vector<int>> edges;
};

}  // namespace circuit
}  // namespace qstabr

#endif
