#ifndef CIRCUIT_DIAGONALISER_H_
#define CIRCUIT_DIAGONALISER_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pauli_exponential.h"
#include "qubit_manager.h"

namespace qstabr {
namespace circuit {

class Diagonaliser {
 public:
  Diagonaliser(std::unordered_map<int, PauliExponential> &paulis,
               int numQubits);

  std::vector<CliffordGate> Diagonalise(const std::vector<int> &group);

 private:
  void Print();

  void ResetState(const std::vector<int> &group);

  void ConjugateForDiag(int qubit, PauliLetter letter);

  bool DiagonaliseTrivial(int qubit);
  bool DiagonaliseCompatible();

  bool VerifyMinWeight(const std::vector<int> &weightings,
                       const std::vector<int> &newWeightings);
  std::vector<int> DiagonaliseMinWeight();

  std::list<int> qubits;
  std::unordered_set<int> diagonalQubits;
  std::vector<int> group;
  std::vector<CliffordGate> conj;
  std::unordered_map<int, PauliExponential> &paulis;
  int numQubits;
};

}  // namespace circuit
}  // namespace qstabr

#endif