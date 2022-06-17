#include "qubit_manager.h"

#include <cassert>

namespace qstabr {
namespace circuit {

QubitManager::QubitManager() {}

int QubitManager::GetQubitIndex(const Qubit &qubit) {
  auto it = qubits.find(qubit.name);
  assert(it != qubits.end());
  return it->second.firstQubit + qubit.offset;
}

void QubitManager::AddQubits(const std::string &name, int number) {
  qubits.insert({name, {number, nextQubit}});
  nextQubit += number;
}

}  // namespace circuit
}  // namespace qstabr
