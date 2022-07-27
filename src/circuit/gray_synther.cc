#include "gray_synther.h"

#include <cassert>

namespace ast = staq::synthesis::ast;

namespace qstabr {
namespace circuit {

GraySynther::GraySynther(std::unordered_map<int, PauliExponential> &paulis,
                         int numQubits)
    : paulis(paulis), numQubits(numQubits) {}

void GraySynther::GraySynth(std::vector<SimpleGate> &gates,
                            const std::vector<int> &group) {
  std::list<staq::synthesis::phase_term> phases;
  for (const auto pauliIndex : group) {
    phases.push_back(paulis.at(pauliIndex).ToPhaseTerm());
  }

  staq::synthesis::linear_op<bool> base;
  for (int i{}; i < numQubits; i++) {
    std::vector<bool> row(numQubits, false);
    row[i] = true;
    base.push_back(row);
  }

  auto result = staq::synthesis::gray_synth(phases, base);

  for (auto &gate : result) {
    if (std::holds_alternative<std::pair<int, int>>(gate)) {
      auto &cnot = std::get<std::pair<int, int>>(gate);
      gates.push_back(CliffordGate::CreateCNOT(cnot.first, cnot.second));
    } else {
      auto &zgate = std::get<std::pair<ast::ptr<ast::Expr>, int>>(gate);
      auto value = zgate.first->constant_eval();
      assert(value.has_value());
      gates.push_back(ZGate(zgate.second, *value));
    }
  }
}

}  // namespace circuit
}  // namespace qstabr