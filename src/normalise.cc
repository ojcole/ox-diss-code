#include <cassert>
#include <cmath>
#include <iostream>

#include "staq/qasmtools/ast/traversal.hpp"
#include "staq/qasmtools/parser/parser.hpp"
#include "staq/transformations/desugar.hpp"
#include "staq/transformations/inline.hpp"

#define EPSILON 1e-7
#define PI 3.14159265358979323846f
#define PI2 1.57079632679489661923f
#define PI4 0.78539816339744830962f
#define PI8 0.39269908169872415481f

namespace {

void norm(double &num) {
  while (num > PI) num -= 2 * PI;
  while (num < -PI) num += 2 * PI;
}

bool isPi(double num) {
  norm(num);
  return std::abs(std::abs(num) - PI) < EPSILON;
}

bool isZero(double num) {
  norm(num);
  return std::abs(num) < EPSILON;
}

bool isNum(double num, double target) {
  norm(num);
  return std::abs(num - target) < EPSILON;
}

bool isNegNum(double num, double target) { return isNum(num, -target); }

bool isPi2(double num) { return isNum(num, PI2); }

bool isNegPi2(double num) { return isNegNum(num, PI2); }

bool isPi4(double num) { return isNum(num, PI4); }

bool isNegPi4(double num) { return isNegNum(num, PI4); }

bool isPi8(double num) { return isNum(num, PI8); }

bool isNegPi8(double num) { return isNegNum(num, PI8); }

void outputNum(double num, std::ostream &output) {
  if (isPi(num)) {
    output << "pi";
  } else if (isZero(num)) {
    output << "0";
  } else if (isPi2(num)) {
    output << "pi/2";
  } else if (isNegPi2(num)) {
    output << "-pi/2";
  } else if (isPi4(num)) {
    output << "pi/4";
  } else if (isNegPi4(num)) {
    output << "-pi/4";
  } else if (isPi8(num)) {
    output << "pi/8";
  } else if (isNegPi8(num)) {
    output << "-pi/8";
  } else {
    std::streamsize ss = output.precision();
    output << std::setprecision(15) << num << std::setprecision(ss);
  }
}

class GateReader : public qasmtools::ast::Traverse {
 public:
  GateReader(std::ostream &output) : output(output) {}

  void visit(qasmtools::ast::RegisterDecl &reg) override {
    if (reg.is_quantum()) {
      output << "qreg " << reg.id() << "[" << reg.size() << "];" << std::endl;
    }
  }

  void visit(qasmtools::ast::UGate &gate) override {
    const auto &arg = gate.arg();
    const auto &offset = arg.offset();
    auto theta = gate.theta().constant_eval();
    auto phi = gate.phi().constant_eval();
    auto lambda = gate.lambda().constant_eval();
    assert(theta.has_value() && phi.has_value() && lambda.has_value());
    auto thetaVal = *theta;
    auto phiVal = *phi;
    auto lambdaVal = *lambda;
    output << "u3(";
    outputNum(thetaVal, output);
    output << ",";
    outputNum(phiVal, output);
    output << ",";
    outputNum(lambdaVal, output);
    output << ") " << arg.var() << "[" << *offset << "];" << std::endl;
  }

  void visit(qasmtools::ast::CNOTGate &gate) override {
    const auto &control = gate.ctrl();
    const auto &target = gate.tgt();
    const auto &cOffset = control.offset();
    const auto &tOffset = target.offset();
    assert(cOffset.has_value() && tOffset.has_value());
    output << "cx " << control.var() << "[" << *cOffset << "]," << target.var()
           << "[" << *tOffset << "];" << std::endl;
  }

  void visit(qasmtools::ast::DeclaredGate &gate) override {
    auto &expr = gate.carg(0);
    auto &qubit = gate.qarg(0);
    auto exprValue = *expr.constant_eval();
    double thetaVal = 0;
    double phiVal = 0;
    double lambdaVal = 0;
    if (gate.name() == "rz" || gate.name() == "u1") {
      lambdaVal = exprValue;
    } else if (gate.name() == "rx") {
      thetaVal = exprValue;
      phiVal = -PI2;
      lambdaVal = PI2;
    } else if (gate.name() == "ry") {
      thetaVal = exprValue;
    }
    output << "u3(";
    outputNum(thetaVal, output);
    output << ",";
    outputNum(phiVal, output);
    output << ",";
    outputNum(lambdaVal, output);
    output << ") " << qubit.var() << "[" << *qubit.offset() << "];"
           << std::endl;
  }

  void visit(qasmtools::ast::GateDecl &decl) override {}

 private:
  std::ostream &output;
};

}  // namespace

static const std::set<std::string_view> overrides{"rx", "ry", "rz", "u1"};

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cerr << "Requires a file path argument" << std::endl;
    return 1;
  }

  auto ast = qasmtools::parser::parse_file(argv[1]);

  staq::transformations::desugar(*ast);
  staq::transformations::Inliner::config config = {false, overrides};
  staq::transformations::inline_ast(*ast, config);

  std::ostream &stream = std::cout;
  stream << "OPENQASM 2.0;" << std::endl;
  stream << "include \"qelib1.inc\";" << std::endl;
  GateReader reader(stream);
  ast->accept(reader);
}
