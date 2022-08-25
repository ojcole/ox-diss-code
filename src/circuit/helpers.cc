#include "helpers.h"

// Fix issue with staq library not including unordered map
#include <unordered_map>

#include "staq/transformations/desugar.hpp"
#include "staq/transformations/inline.hpp"

namespace qstabr {
namespace circuit {

namespace {

std::unique_ptr<qasmtools::ast::Expr> GetPIByTwo() {
  auto pi = qasmtools::ast::PiExpr::create({});
  auto two = qasmtools::ast::IntExpr::create({}, 2);
  return qasmtools::ast::BExpr::create(
      {}, std::move(pi), qasmtools::ast::BinaryOp::Divide, std::move(two));
}

const double EPSILON = 1e-6;
const double PI = 3.14159265358979323846;
const double PI2 = 1.57079632679489661923;

void norm(double &num) { num -= 2 * PI * std::round(num / (2 * PI)); }

}  // namespace

void NormaliseProgram(qasmtools::ast::Program &program) {
  staq::transformations::desugar(program);

  staq::transformations::Inliner::config config = {
      false, std::set<std::string_view>()};

  staq::transformations::inline_ast(program, config);
}

std::unique_ptr<qasmtools::ast::Expr> AddPIByTwoToPhase(
    const qasmtools::ast::Expr &expr) {
  return qasmtools::ast::BExpr::create({}, qasmtools::ast::object::clone(expr),
                                       qasmtools::ast::BinaryOp::Plus,
                                       GetPIByTwo());
}

std::unique_ptr<qasmtools::ast::Expr> SubtractPIByTwoFromPhase(
    const qasmtools::ast::Expr &expr) {
  return qasmtools::ast::BExpr::create({}, qasmtools::ast::object::clone(expr),
                                       qasmtools::ast::BinaryOp::Minus,
                                       GetPIByTwo());
}

std::unique_ptr<qasmtools::ast::Expr> AddExprPhases(
    const qasmtools::ast::Expr &lhs, const qasmtools::ast::Expr &rhs) {
  return qasmtools::ast::BExpr::create({}, qasmtools::ast::object::clone(lhs),
                                       qasmtools::ast::BinaryOp::Plus,
                                       qasmtools::ast::object::clone(rhs));
}

std::unique_ptr<qasmtools::ast::Expr> SubtractExprPhases(
    const qasmtools::ast::Expr &lhs, const qasmtools::ast::Expr &rhs) {
  return qasmtools::ast::BExpr::create({}, qasmtools::ast::object::clone(lhs),
                                       qasmtools::ast::BinaryOp::Minus,
                                       qasmtools::ast::object::clone(rhs));
}

std::unique_ptr<qasmtools::ast::Expr> NegateExprPhase(
    const qasmtools::ast::Expr &expr) {
  return qasmtools::ast::UExpr::create({}, qasmtools::ast::UnaryOp::Neg,
                                       qasmtools::ast::object::clone(expr));
}

bool isPi(double num) {
  norm(num);
  return std::abs(std::abs(num) - PI) < EPSILON;
}

bool isZero(double num) {
  norm(num);
  return std::abs(num) < EPSILON;
}

bool isPi2(double num) {
  norm(num);
  return std::abs(num - PI2) < EPSILON;
}

bool isNegPi2(double num) {
  norm(num);
  return std::abs(num + PI2) < EPSILON;
}

std::optional<phase::RationalPhase> CliffordPhaseFromDouble(double phase) {
  if (isPi(phase)) return phase::PI;
  if (isZero(phase)) return phase::ZERO;
  if (isPi2(phase)) return phase::PI_BY_2;
  if (isNegPi2(phase)) return phase::MINUS_PI_BY_2;
  return std::nullopt;
}

}  // namespace circuit
}  // namespace qstabr
