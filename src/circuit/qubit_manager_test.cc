#include "qubit_manager.h"

#include <gtest/gtest.h>

#include <sstream>

#define QUBIT "qubit"

namespace {

using namespace qstabr;
using namespace circuit;

TEST(Synthesise, Single) {
  QubitManager manager;
  manager.AddQubits(QUBIT, 5);

  std::stringstream output;
  manager.Synthesise(output);
  ASSERT_EQ(output.str(), "qreg qubit[5];\n");
}

TEST(Synthesise, SameOrder) {
  QubitManager manager;
  manager.AddQubits(QUBIT, 5);
  manager.AddQubits("a" QUBIT, 5);
  manager.AddQubits("b" QUBIT, 5);

  std::stringstream output;
  manager.Synthesise(output);
  ASSERT_EQ(output.str(),
            "qreg " QUBIT "[5];\nqreg a" QUBIT "[5];\nqreg b" QUBIT "[5];\n");
}

TEST(QubitIndex, Correctness) {
  QubitManager manager;
  manager.AddQubits(QUBIT, 5);
  manager.AddQubits("a" QUBIT, 5);
  manager.AddQubits("b" QUBIT, 5);

  for (int i{}; i < 5; i++) {
    ASSERT_EQ(manager.GetQubitIndex({QUBIT, i}), i);
  }

  for (int i{}; i < 5; i++) {
    ASSERT_EQ(manager.GetQubitIndex({"a" QUBIT, i}), i + 5);
  }

  for (int i{}; i < 5; i++) {
    ASSERT_EQ(manager.GetQubitIndex({"b" QUBIT, i}), i + 10);
  }
}

TEST(IndexQubit, Correctness) {
  QubitManager manager;
  manager.AddQubits(QUBIT, 5);
  manager.AddQubits("a" QUBIT, 5);
  manager.AddQubits("b" QUBIT, 5);

  for (int i{}; i < 5; i++) {
    ASSERT_EQ(manager.GetIndexQubit(i).name, QUBIT);
    ASSERT_EQ(manager.GetIndexQubit(i).offset, i);
  }

  for (int i{}; i < 5; i++) {
    ASSERT_EQ(manager.GetIndexQubit(i + 5).name, "a" QUBIT);
    ASSERT_EQ(manager.GetIndexQubit(i + 5).offset, i);
  }

  for (int i{}; i < 5; i++) {
    ASSERT_EQ(manager.GetIndexQubit(i + 10).name, "b" QUBIT);
    ASSERT_EQ(manager.GetIndexQubit(i + 10).offset, i);
  }
}

TEST(QubitCount, Correctness) {
  QubitManager manager;

  ASSERT_EQ(manager.GetNumQubits(), 0);

  manager.AddQubits(QUBIT, 5);

  ASSERT_EQ(manager.GetNumQubits(), 5);

  manager.AddQubits("a" QUBIT, 5);

  ASSERT_EQ(manager.GetNumQubits(), 10);

  manager.AddQubits("b" QUBIT, 5);

  ASSERT_EQ(manager.GetNumQubits(), 15);
}

}  // namespace