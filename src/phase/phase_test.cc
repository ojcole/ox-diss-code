#include "phase.h"

#include <gtest/gtest.h>

#include <iostream>

#include "staq/qasmtools/ast/expr.hpp"

namespace {

using namespace qstabr;

using ExprPTR = std::unique_ptr<qasmtools::ast::Expr>;

ExprPTR PI() { return qasmtools::ast::PiExpr::create({}); }

ExprPTR Int(int num) { return qasmtools::ast::IntExpr::create({}, num); }

ExprPTR operator+(ExprPTR&& expr1, ExprPTR&& expr2) {
  return qasmtools::ast::BExpr::create(
      {}, std::move(expr1), qasmtools::ast::BinaryOp::Plus, std::move(expr2));
}

ExprPTR operator-(ExprPTR&& expr1, ExprPTR&& expr2) {
  return qasmtools::ast::BExpr::create(
      {}, std::move(expr1), qasmtools::ast::BinaryOp::Minus, std::move(expr2));
}

ExprPTR operator-(ExprPTR&& expr1) {
  return qasmtools::ast::UExpr::create({}, qasmtools::ast::UnaryOp::Neg,
                                       std::move(expr1));
}

ExprPTR operator*(ExprPTR&& expr1, ExprPTR&& expr2) {
  return qasmtools::ast::BExpr::create(
      {}, std::move(expr1), qasmtools::ast::BinaryOp::Times, std::move(expr2));
}

ExprPTR operator/(ExprPTR&& expr1, ExprPTR&& expr2) {
  return qasmtools::ast::BExpr::create(
      {}, std::move(expr1), qasmtools::ast::BinaryOp::Divide, std::move(expr2));
}

TEST(EqualityTest, FullConstructor) {}

TEST(GetRationalPhaseFromExprTest, Addition) {
  {
    ExprPTR expr = (((-PI() / Int(4)) + (PI() / Int(4))) + (-PI() / Int(4))) +
                   (PI() / Int(4));
    auto phase = phase::GetRationalPhaseFromExpr(*expr);
    ASSERT_EQ(phase.GetFraction().GetNumerator(), 0);
    ASSERT_EQ(phase.GetFraction().GetDenominator(), 1);
  }
  {
    ExprPTR expr = (-PI() / Int(4)) + (PI() / Int(4));
    auto phase = phase::GetRationalPhaseFromExpr(*expr);
    ASSERT_EQ(phase.GetFraction().GetNumerator(), 0);
    ASSERT_EQ(phase.GetFraction().GetDenominator(), 1);
  }
  {
    ExprPTR expr = (Int(3) * PI() / Int(4)) + (PI() / Int(4));
    auto phase = phase::GetRationalPhaseFromExpr(*expr);
    ASSERT_EQ(phase.GetFraction().GetNumerator(), 1);
    ASSERT_EQ(phase.GetFraction().GetDenominator(), 1);
  }
  {
    ExprPTR expr = PI() - PI();
    auto phase = phase::GetRationalPhaseFromExpr(*expr);
    ASSERT_EQ(phase.GetFraction().GetNumerator(), 0);
    ASSERT_EQ(phase.GetFraction().GetDenominator(), 1);
  }
}

}  // namespace