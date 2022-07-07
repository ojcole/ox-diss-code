#ifndef CIRCUIT_CLIFFORD_GATE_H_
#define CIRCUIT_CLIFFORD_GATE_H_

#include <optional>

#include "phase/phase.h"
#include "qubit.h"

namespace qstabr {
namespace circuit {

enum GateType { CNOT, ZROT, XROT, HAD };

class CliffordGate {
 public:
  GateType GetGateType() const;
  Qubit GetFirstQubit() const;
  Qubit GetSecondQubit() const;
  std::optional<phase::RationalPhase> GetPhase() const;

  void Synthesise(std::ostream &output) const;

  static CliffordGate CreateCNOT(Qubit control, Qubit target);
  static CliffordGate CreateHAD(Qubit qubit);
  static CliffordGate CreateZRot(Qubit qubit,
                                 const phase::RationalPhase &phase);
  static CliffordGate CreateXRot(Qubit qubit,
                                 const phase::RationalPhase &phase);

 private:
  CliffordGate(GateType type, Qubit qubit1, Qubit qubit2 = {},
               const std::optional<phase::RationalPhase> &phase = std::nullopt);

  GateType type;
  Qubit qubit1;
  Qubit qubit2;
  std::optional<phase::RationalPhase> phase;
};

}  // namespace circuit
}  // namespace qstabr

#endif