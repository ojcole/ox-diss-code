#include "clifford_gate.h"

namespace qstabr {
namespace circuit {

GateType CliffordGate::GetGateType() const { return type; }

Qubit CliffordGate::GetFirstQubit() const { return qubit1; }

Qubit CliffordGate::GetSecondQubit() const { return qubit2; }

std::optional<phase::RationalPhase> CliffordGate::GetPhase() const {
  return phase;
}

CliffordGate CliffordGate::CreateCNOT(Qubit control, Qubit target) {
  return CliffordGate(CNOT, control, target);
}

CliffordGate CliffordGate::CreateHAD(Qubit qubit) {
  return CliffordGate(HAD, qubit);
}

CliffordGate CliffordGate::CreateZRot(Qubit qubit,
                                      const phase::RationalPhase &phase) {
  return CliffordGate(ZROT, qubit, {}, phase);
}

CliffordGate CliffordGate::CreateXRot(Qubit qubit,
                                      const phase::RationalPhase &phase) {
  return CliffordGate(XROT, qubit, {}, phase);
}

CliffordGate::CliffordGate(GateType type, Qubit qubit1, Qubit qubit2,
                           const std::optional<phase::RationalPhase> &phase)
    : type(type), qubit1(qubit1), qubit2(qubit2), phase(phase) {}

}  // namespace circuit
}  // namespace qstabr