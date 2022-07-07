#ifndef CIRCUIT_Z_GATE_H_
#define CIRCUIT_Z_GATE_H_

#include <optional>

#include "qubit.h"

namespace qstabr {
namespace circuit {

class ZGate {
 public:
  ZGate(Qubit qubit, double angle);

  Qubit GetQubit() const;
  double GetAngle() const;

  void Synthesise(std::ostream &output) const;

 private:
  Qubit qubit;
  double angle;
};

}  // namespace circuit
}  // namespace qstabr

#endif