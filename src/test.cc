#include <iostream>

#include "circuit/single_qubit_unitary.h"
#include "phase/phase.h"

using namespace qstabr;

const double EPSILON = 1e-6;
const double PI = 3.14159265359f;
const double PI2 = 1.57079632679f;

void norm(double& num) { num -= 2 * PI * std::round(num / (2 * PI)); }

bool isPi(double num) {
  norm(num);
  return std::abs(std::abs(num) - PI) < EPSILON;
}

int main(int argc, char const* argv[]) {
  circuit::QubitManager manager;
  manager.AddQubits("qubit", 1);
  circuit::SingleQubitUnitary unitary(0);
  unitary.AddZPhase(phase::PI_BY_2);
  unitary.AddXPhase(phase::PI_BY_2);
  unitary.AddZPhase(phase::PI_BY_2);
  unitary.AddXPhase(phase::PI);
  unitary.AddXPhase(phase::PI_BY_2);
  unitary.Synthesise(std::cout, manager);
}
