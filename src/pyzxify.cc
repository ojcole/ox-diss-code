#include <cassert>
#include <cmath>
#include <iostream>

#include "circuit/helpers.h"
#include "staq/qasmtools/ast/traversal.hpp"
#include "staq/qasmtools/parser/parser.hpp"

#define EPSILON 1e-6
#define PI 3.14159265359f
#define PI2 1.57079632679f

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

bool isPi2(double num) {
  norm(num);
  return std::abs(num - PI2) < EPSILON;
}

bool isNegPi2(double num) {
  norm(num);
  return std::abs(num + PI2) < EPSILON;
}

void outputNum(double num, std::ostream &output) {
  if (isPi(num)) {
    output << "pi";
  } else if (isZero(num)) {
    output << "0";
  } else if (isPi2(num)) {
    output << "pi/2";
  } else if (isNegPi2(num)) {
    output << "-pi/2";
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

 private:
  std::ostream &output;
};

}  // namespace

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cerr << "Requires a file path argument" << std::endl;
    return 1;
  }

  auto ast = qasmtools::parser::parse_file(argv[1]);
  qstabr::circuit::NormaliseProgram(*ast);
  std::ostream &stream = std::cout;
  stream << "OPENQASM 2.0;" << std::endl;
  stream << "include \"qelib1.inc\";" << std::endl;
  GateReader reader(stream);
  ast->accept(reader);
}
