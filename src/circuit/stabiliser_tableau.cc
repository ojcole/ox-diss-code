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
  const auto qubitIndex = qubitManager->GetQubitIndex(qubit);
  ApplyUnitaryGate(qubitIndex, theta, phi, lambda);
}

void StabiliserTableau::ApplyUnitaryGate(int qubit,
                                         const phase::RationalPhase &theta,
                                         const phase::RationalPhase &phi,
                                         const phase::RationalPhase &lambda) {
  auto phiTmp(phi);
  auto lambdaTmp(lambda);
  phiTmp += phase::PI_BY_2;
  lambdaTmp -= phase::PI_BY_2;
  ApplyZRot(qubit, lambdaTmp);
  ApplyXRot(qubit, theta);
  ApplyZRot(qubit, phiTmp);
}

void StabiliserTableau::ApplyXRot(const Qubit &qubit,
                                  const phase::RationalPhase &phase) {
  const auto qubitIndex = qubitManager->GetQubitIndex(qubit);
  ApplyXRot(qubitIndex, phase);
}

void StabiliserTableau::ApplyXRot(int qubit,
                                  const phase::RationalPhase &phase) {
  ApplyHadamard(qubit);
  ApplyZRot(qubit, phase);
  ApplyHadamard(qubit);
}

void StabiliserTableau::ApplyZRot(int qubit,
                                  const phase::RationalPhase &phase) {
  int iters =
      (static_cast<int>(phase.GetFraction() / phase::PI_BY_2.GetFraction()) +
       4) %
      4;
  for (int j{}; j < iters; j++) {
    for (int i{}; i < 2 * numQubits; i++) {
      grid[i][2 * numQubits] ^= grid[i][qubit] * grid[i][qubit + numQubits];
      grid[i][qubit + numQubits] ^= grid[i][qubit];
    }
  }
}

void StabiliserTableau::ApplyZRot(const Qubit &qubit,
                                  const phase::RationalPhase &phase) {
  int qubitIndex = qubitManager->GetQubitIndex(qubit);
  ApplyZRot(qubitIndex, phase);
}

void StabiliserTableau::ApplyPhase(int qubit) {
  ApplyZRot(qubit, phase::PI_BY_2);
}

void StabiliserTableau::ApplyPhase(const Qubit &qubit) {
  int qubitIndex = qubitManager->GetQubitIndex(qubit);
  ApplyPhase(qubitIndex);
}

void StabiliserTableau::ApplyCNOTGate(int control, int target) {
  for (int i{}; i < 2 * numQubits; i++) {
    grid[i][2 * numQubits] ^=
        grid[i][control] * grid[i][target + numQubits] *
        (grid[i][target] ^ grid[i][control + numQubits] ^ 1);
    grid[i][target] ^= grid[i][control];
    grid[i][control + numQubits] ^= grid[i][target + numQubits];
  }
}

void StabiliserTableau::ApplyCNOTGate(const Qubit &control,
                                      const Qubit &target) {
  int ctrlIndex = qubitManager->GetQubitIndex(control);
  int tgtIndex = qubitManager->GetQubitIndex(target);
  ApplyCNOTGate(ctrlIndex, tgtIndex);
}

void StabiliserTableau::ApplyHadamard(const Qubit &qubit) {
  int qubitIndex = qubitManager->GetQubitIndex(qubit);
  ApplyHadamard(qubitIndex);
}

void StabiliserTableau::ApplyHadamard(int qubit) {
  for (int i{}; i < 2 * numQubits; i++) {
    grid[i][2 * numQubits] ^= grid[i][qubit] * grid[i][qubit + numQubits];
    std::swap(grid[i][qubit], grid[i][qubit + numQubits]);
  }
}

void StabiliserTableau::ApplyCliffordGate(const CliffordGate &clifford) {
  switch (clifford.GetGateType()) {
    case GateType::HAD:
      ApplyHadamard(clifford.GetFirstQubit());
      break;
    case GateType::CNOT:
      ApplyCNOTGate(clifford.GetFirstQubit(), clifford.GetSecondQubit());
      break;
    case GateType::XROT:
      ApplyXRot(clifford.GetFirstQubit(), *clifford.GetPhase());
      break;
    case GateType::ZROT:
      ApplyZRot(clifford.GetFirstQubit(), *clifford.GetPhase());
      break;
    default:
      throw std::runtime_error("Unknown gate type");
  }
}

void StabiliserTableau::ApplyCliffordPauliExponential(
    const PauliExponential &pauli) {
  auto phase = phase::GetRationalPhaseFromExpr(pauli.GetExpr());
  if (pauli.IsNegated()) phase *= -1;
  assert(phase.IsClifford());
  std::vector<SimpleGate> gates;
  pauli.Synthesise(gates);
  for (const auto &gate : gates) {
    if (std::holds_alternative<CliffordGate>(gate)) {
      ApplyCliffordGate(std::get<CliffordGate>(gate));
    } else {
      assert(std::holds_alternative<ZGate>(gate));
      auto &zgate = std::get<ZGate>(gate);
      ApplyZRot(zgate.GetQubit(), phase);
    }
  }
}

void StabiliserTableau::ShiftPauliExponential(PauliExponential &pauli) {
  const auto &stringCopy = pauli.GetString();
  PauliString baseString(std::vector<PauliLetter>(numQubits, I));

  for (int i{}; i < numQubits; i++) {
    if (stringCopy[i] == X || stringCopy[i] == Y) {
      baseString *= GetDestabiliserString(i);
    }
    if (stringCopy[i] == Z || stringCopy[i] == Y) {
      baseString *= GetStabiliserString(i);
    }
  }

  assert(!pauli.IsNegated());
  pauli.SetPauliString(std::move(baseString));
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

void AddRows(std::vector<std::vector<int>> &mat, int row1, int row2) {
  const auto &row1Vec = mat[row1];
  auto &row2Vec = mat[row2];
  for (size_t i{}; i < row1Vec.size(); i++) {
    row2Vec[i] ^= row1Vec[i];
  }
}

void AddRows(std::vector<std::vector<int>> &augMat, std::vector<int> &vec,
             int row1, int row2) {
  AddRows(augMat, row1, row2);
  vec[row2] ^= vec[row1];
}

void SwapRows(std::vector<std::vector<int>> &augMat, std::vector<int> &vec,
              int row1, int row2) {
  std::iter_swap(augMat.begin() + row1, augMat.begin() + row2);
  std::iter_swap(vec.begin() + row1, vec.begin() + row2);
}

}  // namespace

PauliString StabiliserTableau::GetStabiliserString(int index) const {
  return GetString(index + numQubits);
}

PauliString StabiliserTableau::GetDestabiliserString(int index) const {
  return GetString(index);
}

PauliString StabiliserTableau::GetString(int index) const {
  std::vector<PauliLetter> string;
  for (int i{}; i < numQubits; i++) {
    if (grid[index][i] == 1 && grid[index][i + numQubits] == 1) {
      string.push_back(Y);
    } else if (grid[index][i] == 0 && grid[index][i + numQubits] == 1) {
      string.push_back(Z);
    } else if (grid[index][i] == 1 && grid[index][i + numQubits] == 0) {
      string.push_back(X);
    } else {
      string.push_back(I);
    }
  }
  return {string, grid[index][2 * numQubits] == 1};
}

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

  PauliString baseString(std::vector<PauliLetter>(numQubits, I));
  for (int i{}; i < numQubits; i++) {
    if (targetMat[i] == 1) {
      auto str = GetStabiliserString(i);
      auto prod = PauliString::StringMultiply(baseString, str);
      if (prod.first) negated ^= 1;
      baseString = prod.second;
    }
  }

  for (int i{}; i < numQubits; i++) {
    if (targetMat[i] == 1) negated ^= grid[numQubits + i][2 * numQubits];
  }

  return negated == 1;
}

std::vector<PauliString> StabiliserTableau::GetStabilisers() const {
  std::vector<PauliString> stabilisers;
  for (int i{}; i < numQubits; i++) {
    stabilisers.push_back(GetStabiliserString(i));
  }
  return stabilisers;
}

void StabiliserTableau::MakeCFullRank(SynthVec &output) {
  // Only care about the stabiliser matrix
  int nextDepth{};
  auto gridCopy = grid;
  for (int i{}; i < numQubits; i++) {
    int j{nextDepth};
    while (j < numQubits && grid[numQubits + j][i] != 1) j++;
    if (j >= numQubits) continue;
    if (j != nextDepth) AddRows(grid, numQubits + j, numQubits + nextDepth);
    for (int j{nextDepth + 1}; j < numQubits; j++) {
      if (grid[numQubits + j][i] == 1) {
        AddRows(grid, numQubits + nextDepth, numQubits + j);
      }
    }
    nextDepth++;
  }

  int k = nextDepth;
  std::vector<int> cols;
  std::vector<std::vector<int>> augMat;
  for (int i{}; i < numQubits - k; i++) {
    augMat.push_back({});
  }
  for (int i{}; i < numQubits; i++) {
    auto copy = augMat;
    bool ind = false;
    for (int j{}; j < numQubits - k; j++) {
      copy[j].push_back(grid[numQubits + k + j][numQubits + i]);
      if (copy[j].back() == 1) ind = true;
    }
    if (!ind) continue;
    // Perform elim to check independence
    for (size_t x{}; x < copy[0].size(); x++) {
      size_t j{x};
      while (j < copy.size() && copy[j][x] != 1) j++;
      if (j >= copy.size()) {
        ind = false;
        break;
      }
      if (j != x) AddRows(copy, j, x);
      for (size_t j{x + 1}; j < copy.size(); j++) {
        if (copy[j][x] == 1) {
          AddRows(copy, x, j);
        }
      }
    }
    if (ind) {
      for (int j{}; j < numQubits - k; j++) {
        augMat[j].push_back(grid[numQubits + k + j][numQubits + i]);
      }
      cols.push_back(i);
    }
  }

  grid = gridCopy;

  for (size_t i{}; i < cols.size(); i++) {
    ApplyHadamard(cols[i]);
    output.push_back({HAD, cols[i]});
  }
}

void StabiliserTableau::EliminateC(SynthVec &output, int rowOffset,
                                   int colOffset) {
  for (int i{}; i < numQubits; i++) {
    int j{i};
    while (j < numQubits && grid[rowOffset + i][colOffset + j] != 1) j++;
    if (j != i) {
      ApplyCNOTGate(j, i);
      output.push_back({CNOT, j, i});
    }
    for (int j{}; j < numQubits; j++) {
      if (j == i) continue;
      if (grid[rowOffset + i][colOffset + j] == 1) {
        ApplyCNOTGate(i, j);
        output.push_back({CNOT, i, j});
      }
    }
  }
}

void StabiliserTableau::MMStab(SynthVec &output, int rowOffset, int colOffset) {
  std::vector<std::vector<int>> M;
  for (int i{}; i < numQubits; i++) {
    std::vector<int> row;
    for (int j{}; j < numQubits; j++) {
      if (i < j) {
        row.push_back(0);
      } else if (i == j) {
        row.push_back(1);
      } else {
        int total = grid[rowOffset + i][colOffset + j];
        for (int k{}; k < j; k++) {
          total -= row[k] * M[j][k];
        }
        row.push_back(total & 1);
      }
    }
    M.push_back(row);
  }
  for (int i{}; i < numQubits; i++) {
    int lambda = 0;
    for (int k{}; k < numQubits; k++) {
      lambda += M[i][k] * M[i][k];
    }
    lambda -= grid[rowOffset + i][colOffset + i];
    if ((lambda & 1) == 1) {
      // OUTPUT PHASE
      ApplyPhase(i);
      output.push_back({PHASE, i});
    }
  }
  for (int i{}; i < numQubits; i++) {
    for (int j{i + 1}; j < numQubits; j++) {
      if (M[j][i] == 1) {
        ApplyCNOTGate(j, i);
        output.push_back({CNOT, j, i});
      }
    }
  }
}

void StabiliserTableau::ClearM(SynthVec &output, int rowOffset, int colOffset) {
  for (int i{}; i < numQubits; i++) {
    ApplyPhase(i);
    output.push_back({PHASE, i});
  }

  for (int i{}; i < numQubits; i++) {
    if (grid[rowOffset + i][2 * numQubits] == 1) {
      ApplyPhase(i);
      ApplyPhase(i);
      output.push_back({PHASE, i});
      output.push_back({PHASE, i});
    }
  }

  EliminateC(output, rowOffset, colOffset);
}

void StabiliserTableau::Synthesise(std::vector<SimpleGate> &gates) {
  SynthVec synthesised;

  MakeCFullRank(synthesised);

  EliminateC(synthesised, numQubits, 0);
  MMStab(synthesised, numQubits, numQubits);
  ClearM(synthesised, numQubits, 0);

  for (int i{}; i < numQubits; i++) {
    ApplyHadamard(i);
    synthesised.push_back({HAD, i});
  }

  MMStab(synthesised, 0, numQubits);
  ClearM(synthesised, 0, 0);

  for (auto it = synthesised.rbegin(); it != synthesised.rend(); it++) {
    auto qubit = it->qubit1;
    if (it->type == HAD) {
      gates.push_back(CliffordGate::CreateHAD(qubit));
    } else if (it->type == PHASE) {
      gates.push_back(CliffordGate::CreateZRot(qubit, phase::MINUS_PI_BY_2));
    } else {
      auto qubit2 = it->qubit2;
      gates.push_back(CliffordGate::CreateCNOT(qubit, qubit2));
    }
  }
}

}  // namespace circuit
}  // namespace qstabr