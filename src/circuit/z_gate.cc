#include "z_gate.h"

#include <iomanip>

namespace qstabr {
namespace circuit {

ZGate::ZGate(int qubit, double angle) : qubit(qubit), angle(angle) {}

int ZGate::GetQubit() const { return qubit; }

double ZGate::GetAngle() const { return angle; }

void ZGate::Synthesise(std::ostream &output,
                       const QubitManager &manager) const {
  const auto &q = manager.GetIndexQubit(qubit);
  std::streamsize ss = output.precision();
  output << "u1(" << std::setprecision(15) << angle << std::setprecision(ss)
         << ") " << q << ";" << std::endl;
}

}  // namespace circuit
}  // namespace qstabr
