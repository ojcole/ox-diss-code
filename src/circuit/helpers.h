#ifndef CIRCUIT_HELPERS_H_
#define CIRCUIT_HELPERS_H_

#include <variant>

#include "clifford_gate.h"
#include "single_qubit_unitary.h"
#include "staq/qasmtools/ast/program.hpp"
#include "z_gate.h"

namespace qstabr {
namespace circuit {

using SimpleGate = std::variant<CliffordGate, ZGate>;

using SimpleClifford = std::variant<CliffordGate, SingleQubitUnitary>;

struct SynthOptions {
  int threads = 1;
  bool reduceStrings = true;
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

std::unique_ptr<qasmtools::ast::Expr> NegateExprPhase(
    const qasmtools::ast::Expr &expr);

bool isPi(double num);
bool isZero(double num);
bool isPi2(double num);
bool isNegPi2(double num);

std::optional<phase::RationalPhase> CliffordPhaseFromDouble(double phase);

}  // namespace circuit
}  // namespace qstabr

#endif