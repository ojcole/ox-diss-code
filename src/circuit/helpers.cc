#include "helpers.h"

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

}  // namespace

void NormaliseProgram(qasmtools::ast::Program &program) {
  staq::transformations::desugar(program);

  staq::transformations::Inliner::config config = {
      false, std::set<std::string_view>()};

  staq::transformations::Inliner inliner(config);
  program.accept(inliner);
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

}  // namespace circuit
}  // namespace qstabr