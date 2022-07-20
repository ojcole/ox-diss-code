#ifndef CIRCUIT_Z_GATE_H_
#define CIRCUIT_Z_GATE_H_

#include <optional>

#include "qubit_manager.h"

namespace qstabr {
namespace circuit {

class ZGate {
 public:
  ZGate(int qubit, double angle);

  int GetQubit() const;
  double GetAngle() const;

  void Synthesise(std::ostream &output, const QubitManager &manager) const;

 private:
  int qubit;
  double angle;
};

}  // namespace circuit
}  // namespace qstabr

#endif