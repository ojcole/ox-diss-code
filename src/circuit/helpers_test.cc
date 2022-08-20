#include "helpers.h"

#include <gtest/gtest.h>

#define PI 3.14159265358979323851

namespace {

using namespace qstabr;
using namespace circuit;

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
  ASSERT_FALSE(isPi(0));
}

}  // namespace