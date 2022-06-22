#ifndef CIRCUIT_HELPERS_H_
#define CIRCUIT_HELPERS_H_

#include "staq/qasmtools/ast/program.hpp"

namespace qstabr {
namespace circuit {

struct Qubit {
  const std::string name = "";
  const int offset = -1;
};

void NormaliseProgram(qasmtools::ast::Program &program);

std::unique_ptr<qasmtools::ast::Expr> AddPIByTwoToPhase(
    const qasmtools::ast::Expr &expr);

std::unique_ptr<qasmtools::ast::Expr> SubtractPIByTwoFromPhase(
    const qasmtools::ast::Expr &expr);

std::unique_ptr<qasmtools::ast::Expr> AddExprPhases(
    const qasmtools::ast::Expr &lhs, const qasmtools::ast::Expr &rhs);

std::unique_ptr<qasmtools::ast::Expr> SubtractExprPhases(
    const qasmtools::ast::Expr &lhs, const qasmtools::ast::Expr &rhs);

}  // namespace circuit
}  // namespace qstabr

#endif