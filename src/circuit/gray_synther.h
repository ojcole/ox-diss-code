#ifndef CIRCUIT_GRAY_SYNTH_H_
#define CIRCUIT_GRAY_SYNTH_H_

#include "helpers.h"
#include "pauli_exponential.h"
#include "staq/synthesis/cnot_dihedral.hpp"

namespace qstabr {
namespace circuit {

class GraySynther {
 public:
  GraySynther(std::unordered_map<int, PauliExponential> &paulis, int numQubits);

  void GraySynth(std::vector<SimpleGate> &gates, const std::vector<int> &group);

 private:
  std::unordered_map<int, PauliExponential> &paulis;
  int numQubits;
};

}  // namespace circuit
}  // namespace qstabr

#endif