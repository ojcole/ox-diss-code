#ifndef QUBIT_MANAGER_H_
#define QUBIT_MANAGER_H_

#include <unordered_map>

#include "helpers.h"

namespace qstabr {
namespace circuit {

class QubitManager {
  struct QubitEntry {
    int size;
    int firstQubit;
  };

 public:
  QubitManager();

  void AddQubits(const std::string &name, int number);
  int GetQubitIndex(const Qubit &qubit);

 private:
  int nextQubit = 0;
  std::unordered_map<std::string, QubitEntry> qubits;
};

}  // namespace circuit
}  // namespace qstabr

#endif