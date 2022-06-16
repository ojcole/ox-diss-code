#include "stabiliser_tableau.h"

#include <cassert>
#include <stdexcept>

#include "staq/qasmtools/ast/traversal.hpp"
#include "staq/transformations/desugar.hpp"
#include "staq/transformations/inline.hpp"

namespace qstabr {
namespace circuit {

namespace {

class StabiliserTraversal : public qasmtools::ast::Traverse {
 public:
  StabiliserTraversal(StabiliserTableau &tableau) : tableau(tableau) {}

  void visit(qasmtools::ast::RegisterDecl &reg) override {
    tableau.AddQubits(reg.id(), reg.size());
  }

  void visit(qasmtools::ast::UGate &gate) override {
    const auto &arg = gate.arg();
    const auto &offset = arg.offset();
    assert(offset.has_value());
    tableau.ApplyUnitaryGate({arg.var(), *offset},
                             phase::getRationalPhaseFromExpr(gate.theta()),
                             phase::getRationalPhaseFromExpr(gate.phi()),
                             phase::getRationalPhaseFromExpr(gate.lambda()));
  }

  void visit(qasmtools::ast::CNOTGate &gate) override {
    const auto &control = gate.ctrl();
    const auto &target = gate.tgt();
    const auto &cOffset = control.offset();
    const auto &tOffset = target.offset();
    assert(cOffset.has_value() && tOffset.has_value());
    tableau.ApplyCNOTGate({control.var(), *cOffset}, {target.var(), *tOffset});
  }

 private:
  StabiliserTableau &tableau;
};

}  // namespace

StabiliserTableau::StabiliserTableau() {}

StabiliserTableau::StabiliserTableau(qasmtools::ast::Program &&program)
    : numQubits(program.qubits()) {
  NormaliseProgram(program);
  GenerateTableau(program);
}

void StabiliserTableau::NormaliseProgram(qasmtools::ast::Program &program) {
  staq::transformations::desugar(program);

  staq::transformations::Inliner::config config = {
      false, std::set<std::string_view>()};

  staq::transformations::Inliner inliner(config);
  program.accept(inliner);
}

void StabiliserTableau::GenerateTableau(
    qasmtools::ast::Program &normalisedProgram) {
  grid.resize(2 * numQubits);
  for (int i{}; i < 2 * numQubits; i++) {
    grid[i].resize(2 * numQubits + 1);
    grid[i][i] = 1;
  }

  StabiliserTraversal traversal(*this);
  normalisedProgram.accept(traversal);
}

int StabiliserTableau::GetQubitIndex(const Qubit &qubit) {
  auto it = qubits.find(qubit.name);
  assert(it != qubits.end());
  return it->second.firstQubit + qubit.offset;
}

void StabiliserTableau::AddQubits(const std::string &name, int number) {
  qubits.insert({name, {number, nextQubit}});
  nextQubit += number;
}

void StabiliserTableau::ApplyUnitaryGate(const Qubit &qubit,
                                         const phase::RationalPhase &theta,
                                         const phase::RationalPhase &phi,
                                         const phase::RationalPhase &lambda) {
  auto phiTmp(phi);
  auto lambdaTmp(lambda);
  phiTmp += phase::PI_BY_2;
  lambdaTmp -= phase::PI_BY_2;
  ApplyZRot(qubit, phiTmp);
  ApplyXRot(qubit, theta);
  ApplyZRot(qubit, lambdaTmp);
}

void StabiliserTableau::ApplyXRot(const Qubit &qubit,
                                  const phase::RationalPhase &phase) {
  ApplyHadamard(qubit);
  ApplyZRot(qubit, phase);
  ApplyHadamard(qubit);
}

void StabiliserTableau::ApplyZRot(const Qubit &qubit,
                                  const phase::RationalPhase &phase) {
  int qubitIndex = GetQubitIndex(qubit);
  int iters = (static_cast<int>(phase / phase::PI_BY_2) + 4) % 4;
  std::cout << phase << " " << iters << std::endl;
  for (int j{}; j < iters; j++) {
    for (int i{}; i < 2 * numQubits; i++) {
      grid[i][2 * numQubits] ^=
          grid[i][qubitIndex] * grid[i][qubitIndex + numQubits];
      grid[i][qubitIndex + numQubits] ^= grid[i][qubitIndex];
    }
  }
}

void StabiliserTableau::ApplyCNOTGate(const Qubit &control,
                                      const Qubit &target) {
  int ctrlIndex = GetQubitIndex(control);
  int tgtIndex = GetQubitIndex(target);

  for (int i{}; i < 2 * numQubits; i++) {
    grid[i][2 * numQubits] ^=
        grid[i][ctrlIndex] * grid[i][tgtIndex + numQubits] *
        (grid[i][tgtIndex] ^ grid[i][ctrlIndex + numQubits] ^ 1);
    grid[i][tgtIndex] ^= grid[i][ctrlIndex];
    grid[i][ctrlIndex + numQubits] ^= grid[i][tgtIndex + numQubits];
  }
}

void StabiliserTableau::ApplyHadamard(const Qubit &qubit) {
  int qubitIndex = GetQubitIndex(qubit);
  for (int i{}; i < 2 * numQubits; i++) {
    grid[i][2 * numQubits] ^=
        grid[i][qubitIndex] * grid[i][qubitIndex + numQubits];
    std::swap(grid[i][qubitIndex], grid[i][qubitIndex + numQubits]);
  }
}

void StabiliserTableau::Print() {
  for (int i{}; i < 2 * numQubits; i++) {
    for (int j{}; j < 2 * numQubits + 1; j++) {
      std::cout << grid[i][j] << " ";
    }
    if (grid[i][2 * numQubits] == 0) {
      std::cout << "+";
    } else {
      std::cout << "-";
    }

    for (int j{}; j < numQubits; j++) {
      if (grid[i][j] == 0) {
        if (grid[i][j + numQubits] == 0) {
          std::cout << "I";
        } else {
          std::cout << "Z";
        }
      } else {
        if (grid[i][j + numQubits] == 0) {
          std::cout << "X";
        } else {
          std::cout << "Y";
        }
      }
    }
    std::cout << std::endl;
  }
}

}  // namespace circuit
}  // namespace qstabr