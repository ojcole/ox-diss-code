#include "z_gate.h"

#include <iomanip>

namespace qstabr {
namespace circuit {

ZGate::ZGate(Qubit qubit, double angle) : qubit(qubit), angle(angle) {}

Qubit ZGate::GetQubit() const { return qubit; }

double ZGate::GetAngle() const { return angle; }

void ZGate::Synthesise(std::ostream &output) const {
  std::streamsize ss = output.precision();
  output << "u1(" << std::setprecision(15) << angle << std::setprecision(ss)
         << ") " << qubit << ";" << std::endl;
}

}  // namespace circuit
}  // namespace qstabr
