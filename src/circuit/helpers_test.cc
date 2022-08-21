#include "helpers.h"

#include <gtest/gtest.h>

namespace {

using namespace qstabr;
using namespace circuit;

const double PI = 3.14159265358979323851;

TEST(AddPIByTwo, Correctness) {
  auto expr = qasmtools::ast::RealExpr::create({}, 0.3434);
  auto newExpr = AddPIByTwoToPhase(*expr);
  ASSERT_DOUBLE_EQ(0.3434 + PI / 2.0, *newExpr->constant_eval());
}

TEST(SubPIByTwo, Correctness) {
  auto expr = qasmtools::ast::RealExpr::create({}, 0.3434);
  auto newExpr = SubtractPIByTwoFromPhase(*expr);
  ASSERT_DOUBLE_EQ(0.3434 - PI / 2.0, *newExpr->constant_eval());
}

TEST(AddPhases, Correctness) {
  auto expr1 = qasmtools::ast::RealExpr::create({}, 0.3434);
  auto expr2 = qasmtools::ast::RealExpr::create({}, 0.5654);
  auto newExpr = AddExprPhases(*expr1, *expr2);
  ASSERT_DOUBLE_EQ(0.3434 + 0.5654, *newExpr->constant_eval());
}

TEST(SubPhases, Correctness) {
  auto expr1 = qasmtools::ast::RealExpr::create({}, 0.3434);
  auto expr2 = qasmtools::ast::RealExpr::create({}, 0.5654);
  auto newExpr = SubtractExprPhases(*expr1, *expr2);
  ASSERT_DOUBLE_EQ(0.3434 - 0.5654, *newExpr->constant_eval());
}

TEST(NegatePhase, Correctness) {
  auto expr = qasmtools::ast::RealExpr::create({}, 0.3434);
  auto newExpr = NegateExprPhase(*expr);
  ASSERT_DOUBLE_EQ(-0.3434, *newExpr->constant_eval());
}

TEST(IsPI, Correctness) {
  ASSERT_TRUE(isPi(PI));
  ASSERT_TRUE(isPi(3 * PI));
  ASSERT_TRUE(isPi(-PI));

  ASSERT_FALSE(isPi(PI / 2));
  ASSERT_FALSE(isPi(-PI / 2));
  ASSERT_FALSE(isPi(0));
}

TEST(IsZero, Correctness) {
  ASSERT_TRUE(isZero(0));
  ASSERT_TRUE(isZero(2 * PI));
  ASSERT_TRUE(isZero(-2 * PI));

  ASSERT_FALSE(isZero(PI / 2));
  ASSERT_FALSE(isZero(-PI / 2));
  ASSERT_FALSE(isZero(PI));
}

TEST(IsPi2, Correctness) {
  ASSERT_TRUE(isPi2(PI / 2));
  ASSERT_TRUE(isPi2(5 * PI / 2));
  ASSERT_TRUE(isPi2(-3 * PI / 2));

  ASSERT_FALSE(isPi2(0));
  ASSERT_FALSE(isPi2(-PI / 2));
  ASSERT_FALSE(isPi2(PI));
}

TEST(IsNegPi2, Correctness) {
  ASSERT_TRUE(isNegPi2(-PI / 2));
  ASSERT_TRUE(isNegPi2(3 * PI / 2));
  ASSERT_TRUE(isNegPi2(-5 * PI / 2));

  ASSERT_FALSE(isNegPi2(0));
  ASSERT_FALSE(isNegPi2(PI / 2));
  ASSERT_FALSE(isNegPi2(PI));
}

TEST(CliffordPhase, PIParse) {
  ASSERT_EQ(CliffordPhaseFromDouble(PI), phase::PI);
  ASSERT_EQ(CliffordPhaseFromDouble(-PI), phase::PI);
  ASSERT_EQ(CliffordPhaseFromDouble(3 * PI), phase::PI);

  ASSERT_NE(CliffordPhaseFromDouble(-PI / 2), phase::PI);
  ASSERT_NE(CliffordPhaseFromDouble(0), phase::PI);
  ASSERT_NE(CliffordPhaseFromDouble(PI / 2), phase::PI);
}

TEST(CliffordPhase, PI2Parse) {
  ASSERT_EQ(CliffordPhaseFromDouble(PI / 2), phase::PI_BY_2);
  ASSERT_EQ(CliffordPhaseFromDouble(5 * PI / 2), phase::PI_BY_2);
  ASSERT_EQ(CliffordPhaseFromDouble(-3 * PI / 2), phase::PI_BY_2);

  ASSERT_NE(CliffordPhaseFromDouble(-PI / 2), phase::PI_BY_2);
  ASSERT_NE(CliffordPhaseFromDouble(0), phase::PI_BY_2);
  ASSERT_NE(CliffordPhaseFromDouble(PI), phase::PI_BY_2);
}

TEST(CliffordPhase, NegPI2Parse) {
  ASSERT_EQ(CliffordPhaseFromDouble(-PI / 2), phase::MINUS_PI_BY_2);
  ASSERT_EQ(CliffordPhaseFromDouble(-5 * PI / 2), phase::MINUS_PI_BY_2);
  ASSERT_EQ(CliffordPhaseFromDouble(3 * PI / 2), phase::MINUS_PI_BY_2);

  ASSERT_NE(CliffordPhaseFromDouble(PI / 2), phase::MINUS_PI_BY_2);
  ASSERT_NE(CliffordPhaseFromDouble(0), phase::MINUS_PI_BY_2);
  ASSERT_NE(CliffordPhaseFromDouble(PI), phase::MINUS_PI_BY_2);
}

TEST(CliffordPhase, Zero) {
  ASSERT_EQ(CliffordPhaseFromDouble(0), phase::ZERO);
  ASSERT_EQ(CliffordPhaseFromDouble(2 * PI), phase::ZERO);
  ASSERT_EQ(CliffordPhaseFromDouble(-2 * PI), phase::ZERO);

  ASSERT_NE(CliffordPhaseFromDouble(PI / 2), phase::ZERO);
  ASSERT_NE(CliffordPhaseFromDouble(-PI / 2), phase::ZERO);
  ASSERT_NE(CliffordPhaseFromDouble(PI), phase::ZERO);
}

}  // namespace