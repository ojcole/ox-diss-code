#include "single_qubit_unitary.h"

#include <gtest/gtest.h>

#include <sstream>

#define QUBIT "qubit"

namespace {

using namespace qstabr;
using namespace circuit;

TEST(Simplify, Zero) {
  SingleQubitUnitary unitary{0};
  unitary.AddZPhase(phase::PI_BY_2);
  unitary.AddXPhase(phase::PI_BY_2);
  unitary.AddZPhase(phase::PI_BY_2);
  unitary.AddZPhase(phase::MINUS_PI_BY_2);
  unitary.AddXPhase(phase::MINUS_PI_BY_2);
  unitary.AddZPhase(phase::MINUS_PI_BY_2);
  ASSERT_TRUE(unitary.Simplify());
}

TEST(Simplify, NonZero) {
  SingleQubitUnitary unitary{0};
  unitary.AddZPhase(phase::PI_BY_2);
  unitary.AddXPhase(phase::PI_BY_2);
  unitary.AddZPhase(phase::PI_BY_2);
  unitary.AddZPhase(phase::MINUS_PI_BY_2);
  unitary.AddXPhase(phase::MINUS_PI_BY_2);
  ASSERT_FALSE(unitary.Simplify());
}

TEST(Synthesis, Zero) {
  QubitManager manager;
  manager.AddQubits(QUBIT, 1);

  SingleQubitUnitary unitary{0};
  std::stringstream output;
  unitary.Synthesise(output, manager);
  ASSERT_EQ(output.str(), "");
}

TEST(Synthesis, NonZero) {
  QubitManager manager;
  manager.AddQubits(QUBIT, 1);

  SingleQubitUnitary unitary{0};
  unitary.AddZPhase(phase::PI_BY_2);
  unitary.AddXPhase(phase::PI_BY_2);
  unitary.AddZPhase(phase::PI_BY_2);

  std::stringstream output;
  unitary.Synthesise(output, manager);
  ASSERT_EQ(output.str(), "u3(pi/2,0,pi) " QUBIT "[0];\n");
}

TEST(Synthesis, HadPass) {
  QubitManager manager;
  manager.AddQubits(QUBIT, 1);

  SingleQubitUnitary unitary{0};
  unitary.AddZPhase(phase::PI_BY_2);
  unitary.AddXPhase(phase::PI_BY_2);
  unitary.AddZPhase(phase::PI_BY_2);
  unitary.AddXPhase(phase::MINUS_PI_BY_2);

  std::stringstream output;
  unitary.Synthesise(output, manager);
  ASSERT_EQ(output.str(), "u3(pi/2,pi,pi) " QUBIT "[0];\n");
}

}  // namespace