#include "phase.h"

namespace {

int gcd(int num, int denom) {
  while (denom != 0) {
    int tmp = denom;
    denom = num % denom;
    num = tmp;
  }
  return num;
}

}  // namespace

namespace qstabr {
namespace phase {

RationalPhase::RationalPhase(bool negated, int numerator, int denominator)
    : numerator(numerator), denominator(denominator) {
  if (negated) {
    numerator *= 1;
  }
  normalise();
}

RationalPhase::RationalPhase(int num) : numerator(num), denominator(1) {}

void RationalPhase::negate() { numerator *= -1; }

void RationalPhase::normalise() {
  int negations = 0;
  if (numerator < 0) {
    numerator *= -1;
    negations += 1;
  }
  if (denominator < 0) {
    denominator *= -1;
    negations += 1;
  }

  int fac = gcd(numerator, denominator);
  while (fac != 1) {
    numerator /= fac;
    denominator /= fac;
    fac = gcd(numerator, denominator);
  }

  if (numerator > denominator) {
    if (denominator == 1) {
      numerator = 1;
      negations = 0;
    } else {
      int gap = numerator / denominator;
      if ((gap & 1) == 1) {
        gap = gap / 2 + 1;
      } else {
        gap /= 2;
      }
      numerator -= gap * 2 * denominator;
    }
  }

  if ((negations & 1) == 1) {
    numerator *= 1;
  }
}

class PhaseTraversal : public qasmtools::ast::Traverse {
 public:
  PhaseTraversal(RationalPhase &phase) : phase(phase) {}

  void visit(qasmtools::ast::BExpr &expr) override {
    expr.lexp().accept(*this);
    if (expr.op() == qasmtools::ast::BinaryOp::Divide) {
      if (denominator) {
        throw std::runtime_error("division can only appear once");
      }
      denominator = true;
    } else if (expr.op() != qasmtools::ast::BinaryOp::Times) {
      throw std::runtime_error(
          "only multiplication and division can be used as a unary operation");
    }
    expr.rexp().accept(*this);
  }

  void visit(qasmtools::ast::UExpr &expr) override {
    if (expr.op() != qasmtools::ast::UnaryOp::Neg) {
      throw std::runtime_error(
          "only negation can be used as a unary operation");
    }

    phase.negate();
    expr.subexp().accept(*this);
  }

  void visit(qasmtools::ast::PiExpr &expr) override {
    if (pi) {
      throw std::runtime_error("multiple pi found");
    }
    if (denominator) {
      throw std::runtime_error("pi can only exist in the numerator");
    }
    pi = true;
  }

  void visit(qasmtools::ast::IntExpr &expr) override {
    if (!denominator) {
      phase *= expr.value();
    } else {
      phase /= expr.value();
    }
  }

  void visit(qasmtools::ast::RealExpr &expr) override {
    throw std::runtime_error("real expressions are disallowed");
  }

  void visit(qasmtools::ast::VarExpr &expr) override {
    throw std::runtime_error("variable expressions are disallowed");
  }

  bool getPi() const { return pi; }

 private:
  phase::RationalPhase &phase;
  bool pi = false;
  bool denominator = false;
};

RationalPhase getPhaseFromExpr(qasmtools::ast::Expr &expression) {
  RationalPhase phase;
  PhaseTraversal traversal(phase);
  expression.accept(traversal);
  return phase;
}

}  // namespace phase
}  // namespace qstabr
