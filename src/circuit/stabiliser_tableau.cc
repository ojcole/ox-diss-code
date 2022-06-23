#include "stabiliser_tableau.h"

#include <cassert>
#include <stdexcept>

#include "helpers.h"
#include "staq/qasmtools/ast/traversal.hpp"

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
                             phase::GetRationalPhaseFromExpr(gate.theta()),
                             phase::GetRationalPhaseFromExpr(gate.phi()),
                             phase::GetRationalPhaseFromExpr(gate.lambda()));
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

StabiliserTableau::StabiliserTableau(
    int qubits, const std::shared_ptr<QubitManager> &qubitManager)
    : numQubits(qubits), qubitManager(qubitManager) {
  grid.resize(2 * numQubits);
  for (int i{}; i < 2 * numQubits; i++) {
    grid[i].resize(2 * numQubits + 1);
    grid[i][i] = 1;
  }
}

StabiliserTableau::StabiliserTableau(qasmtools::ast::Program &&program)
    : numQubits(program.qubits()) {
  qubitManager = std::make_shared<QubitManager>();
  NormaliseProgram(program);
  GenerateTableau(program);
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

void StabiliserTableau::AddQubits(const std::string &name, int number) {
  return qubitManager->AddQubits(name, number);
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
  int qubitIndex = qubitManager->GetQubitIndex(qubit);
  int iters =
      (static_cast<int>(phase.GetFraction() / phase::PI_BY_2.GetFraction()) +
       4) %
      4;
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
  int ctrlIndex = qubitManager->GetQubitIndex(control);
  int tgtIndex = qubitManager->GetQubitIndex(target);

  for (int i{}; i < 2 * numQubits; i++) {
    grid[i][2 * numQubits] ^=
        grid[i][ctrlIndex] * grid[i][tgtIndex + numQubits] *
        (grid[i][tgtIndex] ^ grid[i][ctrlIndex + numQubits] ^ 1);
    grid[i][tgtIndex] ^= grid[i][ctrlIndex];
    grid[i][ctrlIndex + numQubits] ^= grid[i][tgtIndex + numQubits];
  }
}

void StabiliserTableau::ApplyHadamard(const Qubit &qubit) {
  int qubitIndex = qubitManager->GetQubitIndex(qubit);
  for (int i{}; i < 2 * numQubits; i++) {
    grid[i][2 * numQubits] ^=
        grid[i][qubitIndex] * grid[i][qubitIndex + numQubits];
    std::swap(grid[i][qubitIndex], grid[i][qubitIndex + numQubits]);
  }
}

void StabiliserTableau::Print() const {
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

namespace {

void AddRows(std::vector<std::vector<int>> &augMat, std::vector<int> &vec,
             int row1, int row2) {
  const auto &row1Vec = augMat[row1];
  auto &row2Vec = augMat[row2];
  for (size_t i{}; i < row1Vec.size(); i++) {
    row2Vec[i] ^= row1Vec[i];
  }
  vec[row2] ^= vec[row1];
}

void SwapRows(std::vector<std::vector<int>> &augMat, std::vector<int> &vec,
              int row1, int row2) {
  std::iter_swap(augMat.begin() + row1, augMat.begin() + row2);
  std::iter_swap(vec.begin() + row1, vec.begin() + row2);
}

}  // namespace

std::optional<bool> StabiliserTableau::CanCreate(
    const PauliString &string) const {
  std::vector<std::vector<int>> augMat;
  std::vector<int> targetMat = string.GetMatrixForm();
  augMat.resize(2 * numQubits);
  for (int i{}; i < 2 * numQubits; i++) {
    augMat[i].resize(numQubits);
    for (int j{}; j < numQubits; j++) {
      augMat[i][j] = grid[numQubits + j][i];
    }
  }

  for (int i{}; i < numQubits; i++) {
    int index = -1;
    for (int j{i}; j < 2 * numQubits; j++) {
      if (augMat[j][i] == 1) {
        index = j;
        break;
      }
    }
    if (index == -1) return std::nullopt;
    if (index != i) {
      SwapRows(augMat, targetMat, i, index);
    }
    for (int j{}; j < 2 * numQubits; j++) {
      if (j == i) continue;
      if (augMat[j][i] == 1) {
        AddRows(augMat, targetMat, i, j);
      }
    }
  }

  for (int i{numQubits}; i < 2 * numQubits; i++) {
    if (targetMat[i] == 1) return std::nullopt;
  }

  int negated = 0;

  for (int i{}; i < numQubits; i++) {
    if (targetMat[i] == 1) negated ^= grid[numQubits + i][2 * numQubits];
  }

  return negated == 1;
}

}  // namespace circuit
}  // namespace qstabr