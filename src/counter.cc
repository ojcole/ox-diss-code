#include "circuit/helpers.h"
#include "circuit/qubit_manager.h"
#include "staq/qasmtools/ast/traversal.hpp"
#include "staq/qasmtools/parser/parser.hpp"

namespace {

using namespace qstabr;

class GateReader : public qasmtools::ast::Traverse {
 public:
  GateReader() {}

  void visit(qasmtools::ast::RegisterDecl &reg) override {
    if (reg.is_quantum()) {
      qubitManager.AddQubits(reg.id(), reg.size());
      for (int i{}; i < reg.size(); i++) {
        tDepth.push_back(0);
        cxDepth.push_back(0);
        gateDepth.push_back(0);
      }
    }
  }

  void visit(qasmtools::ast::UGate &gate) override {
    const auto &arg = gate.arg();
    const auto &offset = arg.offset();
    auto qubit = qubitManager.GetQubitIndex({arg.var(), *offset});

    auto theta =
        circuit::CliffordPhaseFromDouble(*gate.theta().constant_eval());
    auto phi = circuit::CliffordPhaseFromDouble(*gate.phi().constant_eval());
    auto lambda =
        circuit::CliffordPhaseFromDouble(*gate.lambda().constant_eval());

    bool isClifford =
        theta.has_value() && phi.has_value() && lambda.has_value();
    if (!isClifford) {
      tDepth[qubit]++;
    }
    gateDepth[qubit]++;
  }

  void visit(qasmtools::ast::CNOTGate &gate) override {
    const auto &control = gate.ctrl();
    const auto &target = gate.tgt();
    const auto &cOffset = control.offset();
    const auto &tOffset = target.offset();
    auto controlQubit = qubitManager.GetQubitIndex({control.var(), *cOffset});
    auto targetQubit = qubitManager.GetQubitIndex({target.var(), *tOffset});

    cxDepth[controlQubit] =
        std::max(cxDepth[controlQubit], cxDepth[targetQubit]);
    cxDepth[targetQubit] = cxDepth[controlQubit];

    tDepth[controlQubit] = std::max(tDepth[controlQubit], tDepth[targetQubit]);
    tDepth[targetQubit] = tDepth[controlQubit];

    gateDepth[controlQubit] =
        std::max(gateDepth[controlQubit], gateDepth[targetQubit]);
    gateDepth[targetQubit] = gateDepth[controlQubit];

    cxDepth[controlQubit]++;
    cxDepth[targetQubit]++;

    gateDepth[controlQubit]++;
    gateDepth[targetQubit]++;
  }

  int GetTDepth() {
    int maxDepth{};
    for (const auto depth : tDepth) {
      maxDepth = std::max(depth, maxDepth);
    }
    return maxDepth;
  }

  int GetCXDepth() {
    int maxDepth{};
    for (const auto depth : cxDepth) {
      maxDepth = std::max(depth, maxDepth);
    }
    return maxDepth;
  }

  int GetGateDepth() {
    int maxDepth{};
    for (const auto depth : gateDepth) {
      maxDepth = std::max(depth, maxDepth);
    }
    return maxDepth;
  }

 private:
  circuit::QubitManager qubitManager;
  std::vector<int> tDepth;
  std::vector<int> cxDepth;
  std::vector<int> gateDepth;
};

}  // namespace

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cerr << "Requires a file path argument" << std::endl;
    return 1;
  }

  auto ast = qasmtools::parser::parse_file(argv[1]);

  circuit::NormaliseProgram(*ast);

  GateReader reader;
  ast->accept(reader);

  std::cout << "T Depth " << reader.GetTDepth() << std::endl;
  std::cout << "CX Depth " << reader.GetCXDepth() << std::endl;
  std::cout << "Gate Depth " << reader.GetGateDepth() << std::endl;
}
