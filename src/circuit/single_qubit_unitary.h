#ifndef CIRCUIT_SINGLE_QUBIT_UNITARY_H_
#define CIRCUIT_SINGLE_QUBIT_UNITARY_H_

#include "pauli_string.h"
#include "phase/phase.h"
#include "qubit.h"

namespace qstabr {
namespace circuit {

class SingleQubitUnitary {
 public:
  SingleQubitUnitary(const Qubit &qubit);

  void AddZPhase(const phase::RationalPhase &phase);
  void AddXPhase(const phase::RationalPhase &phase);
  void ClearAlpha();
  bool CommutesPast(const PauliLetter letter);
  const Qubit &GetQubit() const;

  void Synthesise(std::ostream &output);

 private:
  void Simplify();

  Qubit qubit;
  phase::RationalPhase alpha;
  phase::RationalPhase beta;
  phase::RationalPhase gamma;
};

}  // namespace circuit
}  // namespace qstabr

#endif