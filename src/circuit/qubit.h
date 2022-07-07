#ifndef CIRCUIT_QUBIT_H_
#define CIRCUIT_QUBIT_H_

#include <ostream>
#include <string>

namespace qstabr {
namespace circuit {

struct Qubit {
  const std::string name = "";
  const int offset = -1;
};

inline std::ostream &operator<<(std::ostream &output, const Qubit &qubit) {
  return output << qubit.name << "[" << qubit.offset << "]";
}

}  // namespace circuit
}  // namespace qstabr

#endif