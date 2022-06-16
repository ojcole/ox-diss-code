#include "clifford_gate.h"

namespace qstabr {
namespace circuit {

GateType CliffordGate::getGateType() const { return type; }

CliffordGate CliffordGate::CreateCNOT(int control, int target) {
  return CliffordGate(CNOT, control, target);
}

CliffordGate CliffordGate::CreateHAD(int qubit) {
  return CliffordGate(HAD, qubit);
}

CliffordGate CliffordGate::CreateZRot(int qubit,
                                      const phase::RationalPhase &phase) {
  return CliffordGate(ZROT, qubit, -1, phase);
}

CliffordGate CliffordGate::CreateXRot(int qubit,
                                      const phase::RationalPhase &phase) {
  return CliffordGate(XROT, qubit, -1, phase);
}

CliffordGate::CliffordGate(
    GateType type, int qubit1, int qubit2,
    const std::optional<phase::RationalPhase> &phase = std::nullopt)
    : type(type), qubit1(qubit1), qubit2(qubit2), phase(phase) {}

}  // namespace circuit
}  // namespace qstabr