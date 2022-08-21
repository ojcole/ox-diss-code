#include "pauli_exponential.h"

#include <gtest/gtest.h>

#include "test_helpers.h"

namespace {

using namespace qstabr;
using namespace circuit;

TEST(CommutationTest, RandomTests) {
  for (int numQubits{}; numQubits < 20; numQubits++) {
    for (int i{}; i < 1000; i++) {
      auto exp1 = RandomPauliExp(numQubits);
      auto exp2 = RandomPauliExp(numQubits);
      ASSERT_EQ(exp1.CommutesWith(exp2),
                exp1.GetString().CommutesWith(exp2.GetString()));
    }
  }
}

TEST(PushThroughTest, ExhaustiveCNOT) {
  auto cnot = CliffordGate::CreateCNOT(0, 1);

  {
    auto exp = CreatePauliExp("IZ"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "ZZ"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("IX"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "IX"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("IY"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "ZY"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("ZI"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "ZI"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("XI"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "XX"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("YI"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "YX"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("ZX"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "ZX"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("ZY"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "IY"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("XY"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "YZ"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("XZ"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "YY"_p);
    ASSERT_TRUE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("YZ"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "XY"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("YX"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "YI"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("ZZ"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "IZ"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("XX"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "XI"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("YY"_p);
    exp.PushCliffordThrough(cnot);
    ASSERT_EQ(exp.GetString(), "XZ"_p);
    ASSERT_TRUE(exp.IsNegated());
  }
}

TEST(PushThroughTest, ExhaustiveRZPI) {
  auto clifford = CliffordGate::CreateZRot(0, phase::PI);
  {
    auto exp = CreatePauliExp("I"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "I"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Z"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Z"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("X"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "X"_p);
    ASSERT_TRUE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Y"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Y"_p);
    ASSERT_TRUE(exp.IsNegated());
  }
}

TEST(PushThroughTest, ExhaustiveRZPIBy2) {
  auto clifford = CliffordGate::CreateZRot(0, phase::PI_BY_2);
  {
    auto exp = CreatePauliExp("I"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "I"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Z"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Z"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("X"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Y"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Y"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "X"_p);
    ASSERT_TRUE(exp.IsNegated());
  }
}

TEST(PushThroughTest, ExhaustiveRZNegPIBy2) {
  auto clifford = CliffordGate::CreateZRot(0, phase::MINUS_PI_BY_2);
  {
    auto exp = CreatePauliExp("I"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "I"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Z"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Z"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("X"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Y"_p);
    ASSERT_TRUE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Y"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "X"_p);
    ASSERT_FALSE(exp.IsNegated());
  }
}

TEST(PushThroughTest, ExhaustiveRZZero) {
  auto clifford = CliffordGate::CreateZRot(0, phase::ZERO);
  {
    auto exp = CreatePauliExp("I"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "I"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Z"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Z"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("X"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "X"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Y"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Y"_p);
    ASSERT_FALSE(exp.IsNegated());
  }
}

TEST(PushThroughTest, ExhaustiveRXPI) {
  auto clifford = CliffordGate::CreateXRot(0, phase::PI);
  {
    auto exp = CreatePauliExp("I"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "I"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Z"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Z"_p);
    ASSERT_TRUE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("X"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "X"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Y"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Y"_p);
    ASSERT_TRUE(exp.IsNegated());
  }
}

TEST(PushThroughTest, ExhaustiveRXPIBy2) {
  auto clifford = CliffordGate::CreateXRot(0, phase::PI_BY_2);
  {
    auto exp = CreatePauliExp("I"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "I"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Z"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Y"_p);
    ASSERT_TRUE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("X"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "X"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Y"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Z"_p);
    ASSERT_FALSE(exp.IsNegated());
  }
}

TEST(PushThroughTest, ExhaustiveRXNegPIBy2) {
  auto clifford = CliffordGate::CreateXRot(0, phase::MINUS_PI_BY_2);
  {
    auto exp = CreatePauliExp("I"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "I"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Z"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Y"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("X"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "X"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Y"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Z"_p);
    ASSERT_TRUE(exp.IsNegated());
  }
}

TEST(PushThroughTest, ExhaustiveRXZero) {
  auto clifford = CliffordGate::CreateXRot(0, phase::ZERO);
  {
    auto exp = CreatePauliExp("I"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "I"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Z"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Z"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("X"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "X"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Y"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Y"_p);
    ASSERT_FALSE(exp.IsNegated());
  }
}

TEST(PushThroughTest, ExhaustiveHAD) {
  auto clifford = CliffordGate::CreateHAD(0);
  {
    auto exp = CreatePauliExp("I"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "I"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Z"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "X"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("X"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Z"_p);
    ASSERT_FALSE(exp.IsNegated());
  }

  {
    auto exp = CreatePauliExp("Y"_p);
    exp.PushCliffordThrough(clifford);
    ASSERT_EQ(exp.GetString(), "Y"_p);
    ASSERT_TRUE(exp.IsNegated());
  }
}

}  // namespace