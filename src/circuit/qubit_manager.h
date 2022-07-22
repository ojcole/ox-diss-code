#ifndef QUBIT_MANAGER_H_
#define QUBIT_MANAGER_H_

#include <unordered_map>
#include <vector>

#include "qubit.h"

namespace qstabr {
namespace circuit {

class QubitManager {
 private:
  struct QubitEntry {
    int size;
    int firstQubit;
  };

 public:
  QubitManager();

  int GetNumQubits() const;
  void AddQubits(const std::string &name, int number);
  int GetQubitIndex(const Qubit &qubit) const;
  const Qubit &GetIndexQubit(int index) const;

  void Synthesise(std::ostream &output) const;

 private:
  int nextQubit = 0;
  std::vector<Qubit> indices;
  std::unordered_map<std::string, QubitEntry> qubits;
  std::vector<std::string> synthQubitOrder;
};

}  // namespace circuit
}  // namespace qstabr

#endif