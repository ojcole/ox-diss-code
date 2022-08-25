#include "clifford_gate.h"

#include <gtest/gtest.h>

#include <sstream>

#include "qubit_manager.h"

#define QUBIT "qubit"

namespace {

using namespace qstabr;
using namespace circuit;

Qubit MkQubit(int num) { return {QUBIT, num}; }

TEST(Dagger, CNOTValid) {
  CliffordGate gate = CliffordGate::CreateCNOT(1, 3);
  auto dagger = gate.Dagger();
  ASSERT_EQ(dagger.GetFirstQubit(), 1);
  ASSERT_EQ(dagger.GetSecondQubit(), 3);
  ASSERT_EQ(dagger.GetGateType(), CNOT);
}

TEST(Dagger, HValid) {
  CliffordGate gate = CliffordGate::CreateHAD(1);
  auto dagger = gate.Dagger();
  ASSERT_EQ(dagger.GetFirstQubit(), 1);
  ASSERT_EQ(dagger.GetGateType(), HAD);
}

TEST(Dagger, RZValid) {
  {
    CliffordGate gate = CliffordGate::CreateZRot(1, phase::PI);
    auto dagger = gate.Dagger();
    ASSERT_EQ(dagger.GetFirstQubit(), 1);
    ASSERT_EQ(dagger.GetGateType(), ZROT);
    ASSERT_EQ(*dagger.GetPhase(), phase::PI);
  }
  {
    CliffordGate gate = CliffordGate::CreateZRot(1, phase::ZERO);
    auto dagger = gate.Dagger();
    ASSERT_EQ(dagger.GetFirstQubit(), 1);
    ASSERT_EQ(dagger.GetGateType(), ZROT);
    ASSERT_EQ(*dagger.GetPhase(), phase::ZERO);
  }
  {
    CliffordGate gate = CliffordGate::CreateZRot(1, phase::PI_BY_2);
    auto dagger = gate.Dagger();
    ASSERT_EQ(dagger.GetFirstQubit(), 1);
    ASSERT_EQ(dagger.GetGateType(), ZROT);
    ASSERT_EQ(*dagger.GetPhase(), phase::MINUS_PI_BY_2);
  }
  {
    CliffordGate gate = CliffordGate::CreateZRot(1, phase::MINUS_PI_BY_2);
    auto dagger = gate.Dagger();
    ASSERT_EQ(dagger.GetFirstQubit(), 1);
    ASSERT_EQ(dagger.GetGateType(), ZROT);
    ASSERT_EQ(*dagger.GetPhase(), phase::PI_BY_2);
  }
}

TEST(Dagger, RXValid) {
  {
    CliffordGate gate = CliffordGate::CreateXRot(1, phase::PI);
    auto dagger = gate.Dagger();
    ASSERT_EQ(dagger.GetFirstQubit(), 1);
    ASSERT_EQ(dagger.GetGateType(), XROT);
    ASSERT_EQ(*dagger.GetPhase(), phase::PI);
  }
  {
    CliffordGate gate = CliffordGate::CreateXRot(1, phase::ZERO);
    auto dagger = gate.Dagger();
    ASSERT_EQ(dagger.GetFirstQubit(), 1);
    ASSERT_EQ(dagger.GetGateType(), XROT);
    ASSERT_EQ(*dagger.GetPhase(), phase::ZERO);
  }
  {
    CliffordGate gate = CliffordGate::CreateXRot(1, phase::PI_BY_2);
    auto dagger = gate.Dagger();
    ASSERT_EQ(dagger.GetFirstQubit(), 1);
    ASSERT_EQ(dagger.GetGateType(), XROT);
    ASSERT_EQ(*dagger.GetPhase(), phase::MINUS_PI_BY_2);
  }
  {
    CliffordGate gate = CliffordGate::CreateXRot(1, phase::MINUS_PI_BY_2);
    auto dagger = gate.Dagger();
    ASSERT_EQ(dagger.GetFirstQubit(), 1);
    ASSERT_EQ(dagger.GetGateType(), XROT);
    ASSERT_EQ(*dagger.GetPhase(), phase::PI_BY_2);
  }
}

TEST(Synthesise, CNOTValid) {
  std::shared_ptr<circuit::QubitManager> manager =
      std::make_shared<circuit::QubitManager>();
  manager->AddQubits(QUBIT, 4);

  {
    CliffordGate gate = CliffordGate::CreateCNOT(1, 3);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "cx " QUBIT "[1]," QUBIT "[3];\n");
  }

  {
    CliffordGate gate = CliffordGate::CreateCNOT(3, 2);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "cx " QUBIT "[3]," QUBIT "[2];\n");
  }
}

TEST(Synthesise, HValid) {
  std::shared_ptr<circuit::QubitManager> manager =
      std::make_shared<circuit::QubitManager>();
  manager->AddQubits(QUBIT, 4);

  {
    CliffordGate gate = CliffordGate::CreateHAD(1);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(pi/2,0,pi) " QUBIT "[1];\n");
  }

  {
    CliffordGate gate = CliffordGate::CreateHAD(2);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(pi/2,0,pi) " QUBIT "[2];\n");
  }
}

TEST(Synthesise, RZValid) {
  std::shared_ptr<circuit::QubitManager> manager =
      std::make_shared<circuit::QubitManager>();
  manager->AddQubits(QUBIT, 4);

  {
    CliffordGate gate = CliffordGate::CreateZRot(1, phase::PI_BY_2);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(0,0,pi/2) " QUBIT "[1];\n");
  }

  {
    CliffordGate gate = CliffordGate::CreateZRot(2, phase::PI_BY_2);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(0,0,pi/2) " QUBIT "[2];\n");
  }

  {
    CliffordGate gate = CliffordGate::CreateZRot(1, phase::ZERO);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(0,0,0) " QUBIT "[1];\n");
  }

  {
    CliffordGate gate = CliffordGate::CreateZRot(1, phase::PI);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(0,0,pi) " QUBIT "[1];\n");
  }

  {
    CliffordGate gate = CliffordGate::CreateZRot(1, phase::MINUS_PI_BY_2);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(0,0,-pi/2) " QUBIT "[1];\n");
  }
}

TEST(Synthesise, RXValid) {
  std::shared_ptr<circuit::QubitManager> manager =
      std::make_shared<circuit::QubitManager>();
  manager->AddQubits(QUBIT, 4);

  {
    CliffordGate gate = CliffordGate::CreateXRot(1, phase::PI_BY_2);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(pi/2,-pi/2,pi/2) " QUBIT "[1];\n");
  }

  {
    CliffordGate gate = CliffordGate::CreateXRot(2, phase::PI_BY_2);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(pi/2,-pi/2,pi/2) " QUBIT "[2];\n");
  }

  {
    CliffordGate gate = CliffordGate::CreateXRot(1, phase::ZERO);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(0,-pi/2,pi/2) " QUBIT "[1];\n");
  }

  {
    CliffordGate gate = CliffordGate::CreateXRot(1, phase::PI);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(pi,-pi/2,pi/2) " QUBIT "[1];\n");
  }

  {
    CliffordGate gate = CliffordGate::CreateXRot(1, phase::MINUS_PI_BY_2);
    std::stringstream stream;
    gate.Synthesise(stream, *manager);
    std::string result = stream.str();
    ASSERT_EQ(result, "u3(-pi/2,-pi/2,pi/2) " QUBIT "[1];\n");
  }
}

}  // namespace