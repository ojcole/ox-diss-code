#ifndef CIRCUIT_SINGLE_QUBIT_UNITARY_H_
#define CIRCUIT_SINGLE_QUBIT_UNITARY_H_

#include "pauli_string.h"
#include "phase/phase.h"
#include "qubit_manager.h"

namespace qstabr {
namespace circuit {

class SingleQubitUnitary {
 public:
  SingleQubitUnitary(int qubit);

  void AddZPhase(const phase::RationalPhase &phase);
  void AddXPhase(const phase::RationalPhase &phase);
  void ClearAlpha();
  bool CommutesPast(const PauliLetter letter);
  int GetQubit() const;

  void Synthesise(std::ostream &output, const QubitManager &manager) const;

  bool Simplify();

 private:
  int qubit;
  phase::RationalPhase alpha;
  phase::RationalPhase beta;
  phase::RationalPhase gamma;
};

}  // namespace circuit
}  // namespace qstabr

#endif