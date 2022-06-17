#include "phase.h"

#include <vector>

namespace qstabr {
namespace phase {

RationalPhase::RationalPhase(Fraction fraction) : fraction(fraction) {
  Normalise();
}

Fraction RationalPhase::getFraction() const { return fraction; }

bool RationalPhase::IsClifford() const {
  const int denom = fraction.getDenominator();
  if (denom < 0) return denom >= -2;
  return denom <= 2;
}

void RationalPhase::Normalise() {
  int numerator = fraction.getNumerator();
  int denominator = fraction.getDenominator();
  bool negated = (numerator < 0) != (denominator < 0);
  if (numerator < 0) numerator *= -1;
  if (denominator < 0) denominator *= -1;

  if (numerator > denominator) {
    if (denominator == 1) {
      if ((numerator & 1) == 1) {
        numerator = 1;
      } else {
        numerator = 0;
      }
      negated = false;
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

  if (negated) {
    numerator *= -1;
  }
  fraction = {numerator, denominator};
}

class PhaseTraversal : public qasmtools::ast::Traverse {
 private:
  struct FractionPI {
    Fraction fraction = 1;
    int piPower = 0;
  };

 public:
  PhaseTraversal() {}

  void visit(qasmtools::ast::BExpr &expr) override {
    expr.lexp().accept(*this);
    expr.rexp().accept(*this);

    auto rFrac = stack.back();
    stack.pop_back();
    auto &lFrac = stack.back();

    switch (expr.op()) {
      case qasmtools::ast::BinaryOp::Divide:
        if (rFrac.fraction == 0) throw PhaseException("Division by zero");
        if (lFrac.fraction != 0) {
          lFrac.fraction /= rFrac.fraction;
          lFrac.piPower -= rFrac.piPower;
        }
        break;
      case qasmtools::ast::BinaryOp::Times:
        if (rFrac.fraction == 0 || lFrac.fraction == 0) {
          lFrac.fraction = 0;
          lFrac.piPower = 0;
        } else {
          lFrac.fraction *= rFrac.fraction;
          lFrac.piPower += rFrac.piPower;
        }
        break;
      case qasmtools::ast::BinaryOp::Minus:
        if (rFrac.fraction == 0) break;
        if (lFrac.fraction == 0) {
          lFrac.fraction = rFrac.fraction * -1;
          lFrac.piPower = rFrac.piPower;
          break;
        }
        if (lFrac.piPower != rFrac.piPower) {
          throw PhaseException("Different powers of pi for minus");
        }
        lFrac.fraction -= rFrac.piPower;
        break;
      case qasmtools::ast::BinaryOp::Plus:
        if (rFrac.fraction == 0 || lFrac.fraction == 0) {
          lFrac = rFrac;
          break;
        }
        if (lFrac.piPower != rFrac.piPower) {
          throw PhaseException("Different powers of pi for plus");
        }
        lFrac.fraction += rFrac.piPower;
        break;
      default:
        throw PhaseException("Unrecognised binary operation");
    }
  }

  void visit(qasmtools::ast::UExpr &expr) override {
    if (expr.op() != qasmtools::ast::UnaryOp::Neg) {
      throw PhaseException("Only negation can be used as a unary operation");
    }
    expr.subexp().accept(*this);
    auto &frac = stack.back();
    frac.fraction *= -1;
  }

  void visit(qasmtools::ast::PiExpr &expr) override { stack.push_back({1, 1}); }

  void visit(qasmtools::ast::IntExpr &expr) override {
    stack.push_back({expr.value(), 0});
  }

  void visit(qasmtools::ast::RealExpr &expr) override {
    throw PhaseException("Real expressions are disallowed");
  }

  void visit(qasmtools::ast::VarExpr &expr) override {
    throw PhaseException("Variable expressions are disallowed");
  }

  RationalPhase getPhase() {
    if (stack.size() != 1) throw PhaseException("Invalid state");

    auto &fraction = stack.back();
    if (fraction.piPower != 1 && fraction.fraction != 0) {
      throw PhaseException("Invalid pi power");
    }
    return fraction.fraction;
  }

 private:
  std::vector<FractionPI> stack;
};

RationalPhase getRationalPhaseFromExpr(qasmtools::ast::Expr &expression) {
  PhaseTraversal traversal;
  expression.accept(traversal);
  return traversal.getPhase();
}

}  // namespace phase
}  // namespace qstabr
