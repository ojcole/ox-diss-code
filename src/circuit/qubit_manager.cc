#include "qubit_manager.h"

#include <cassert>

namespace qstabr {
namespace circuit {

QubitManager::QubitManager() {}

int QubitManager::GetQubitIndex(const Qubit &qubit) const {
  auto it = qubits.find(qubit.name);
  assert(it != qubits.end());
  return it->second.firstQubit + qubit.offset;
}

const Qubit &QubitManager::GetIndexQubit(int index) const {
  return indices[index];
}

void QubitManager::AddQubits(const std::string &name, int number) {
  qubits.insert({name, {number, nextQubit}});
  synthQubitOrder.push_back(name);
  for (int i{}; i < number; i++) {
    indices.push_back({name, i});
  }
  nextQubit += number;
}

void QubitManager::Synthesise(std::ostream &output) {
  for (const auto &name : synthQubitOrder) {
    output << "qreg " << name << "[" << qubits[name].size << "];" << std::endl;
  }
}

}  // namespace circuit
}  // namespace qstabr
