#include "clifford_gate.h"

#include <cassert>

namespace qstabr {
namespace circuit {

GateType CliffordGate::GetGateType() const { return type; }

int CliffordGate::GetFirstQubit() const { return qubit1; }

int CliffordGate::GetSecondQubit() const { return qubit2; }

std::optional<phase::RationalPhase> CliffordGate::GetPhase() const {
  return phase;
}

void CliffordGate::Synthesise(std::ostream &output,
                              const QubitManager &manager) const {
  const Qubit &q1 = manager.GetIndexQubit(qubit1);
  if (type == CNOT) {
    const Qubit &q2 = manager.GetIndexQubit(qubit2);
    output << "cx " << q1 << "," << q2;
  } else if (type == HAD) {
    output << "h " << q1;
  } else if (type == ZROT) {
    output << "u1(" << *phase << ") " << q1;
  } else {
    assert(type == XROT);
    output << "u3(" << *phase << ",-pi/2,pi/2) " << q1;
  }

  output << ";" << std::endl;
}

CliffordGate CliffordGate::CreateCNOT(int control, int target) {
  return CliffordGate(CNOT, control, target);
}

CliffordGate CliffordGate::CreateHAD(int qubit) {
  return CliffordGate(HAD, qubit);
}

CliffordGate CliffordGate::CreateZRot(int qubit,
                                      const phase::RationalPhase &phase) {
  return CliffordGate(ZROT, qubit, {}, phase);
}

CliffordGate CliffordGate::CreateXRot(int qubit,
                                      const phase::RationalPhase &phase) {
  return CliffordGate(XROT, qubit, {}, phase);
}

CliffordGate::CliffordGate(GateType type, int qubit1, int qubit2,
                           const std::optional<phase::RationalPhase> &phase)
    : type(type), qubit1(qubit1), qubit2(qubit2), phase(phase) {}

}  // namespace circuit
}  // namespace qstabr