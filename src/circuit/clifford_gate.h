#ifndef CIRCUIT_CLIFFORD_GATE_H_
#define CIRCUIT_CLIFFORD_GATE_H_

#include <optional>

#include "phase/phase.h"
#include "qubit_manager.h"

namespace qstabr {
namespace circuit {

enum GateType { CNOT, ZROT, XROT, HAD };

class CliffordGate {
 public:
  GateType GetGateType() const;
  int GetFirstQubit() const;
  int GetSecondQubit() const;
  std::optional<phase::RationalPhase> GetPhase() const;

  CliffordGate Dagger() const;

  void Synthesise(std::ostream &output, const QubitManager &manager) const;

  static CliffordGate CreateCNOT(int control, int target);
  static CliffordGate CreateHAD(int qubit);
  static CliffordGate CreateZRot(int qubit, const phase::RationalPhase &phase);
  static CliffordGate CreateXRot(int qubit, const phase::RationalPhase &phase);

 private:
  CliffordGate(GateType type, int qubit1, int qubit2 = {},
               const std::optional<phase::RationalPhase> &phase = std::nullopt);

  GateType type;
  int qubit1;
  int qubit2;
  std::optional<phase::RationalPhase> phase;
};

}  // namespace circuit
}  // namespace qstabr

#endif