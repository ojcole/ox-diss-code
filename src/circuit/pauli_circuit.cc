#include "pauli_circuit.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "helpers.h"
#include "phase/phase.h"
#include "staq/qasmtools/ast/expr.hpp"
#include "staq/qasmtools/ast/traversal.hpp"

namespace qstabr {
namespace circuit {

namespace {

class GateReader : public qasmtools::ast::Traverse {
 public:
  GateReader(PauliCircuit &circuit) : circuit(circuit) {}

  void visit(qasmtools::ast::RegisterDecl &reg) override {
    if (reg.is_quantum()) circuit.AddQubits(reg.id(), reg.size());
  }

  void visit(qasmtools::ast::UGate &gate) override {
    const auto &arg = gate.arg();
    const auto &offset = arg.offset();
    assert(offset.has_value());
    const Qubit qubit = {arg.var(), *offset};

    std::optional<phase::RationalPhase> thetaPhase;
    std::optional<phase::RationalPhase> phiPhase;
    std::optional<phase::RationalPhase> lambdaPhase;
    try {
      const auto phase = phase::GetRationalPhaseFromExpr(gate.theta());
      if (phase.IsClifford()) thetaPhase = phase;
    } catch (const phase::PhaseException &exception) {
    }

    try {
      const auto phase = phase::GetRationalPhaseFromExpr(gate.phi());
      if (phase.IsClifford()) phiPhase = phase;
    } catch (const phase::PhaseException &exception) {
    }

    try {
      const auto phase = phase::GetRationalPhaseFromExpr(gate.lambda());
      if (phase.IsClifford()) lambdaPhase = phase;
    } catch (const phase::PhaseException &exception) {
    }

    if (thetaPhase.has_value() && phiPhase.has_value() &&
        lambdaPhase.has_value()) {
      if ((*phiPhase == phase::ZERO && *thetaPhase == phase::PI_BY_2 &&
           *lambdaPhase == phase::PI) ||
          (*phiPhase == phase::PI && *thetaPhase == phase::MINUS_PI_BY_2 &&
           *lambdaPhase == phase::ZERO)) {
        circuit.AddHadamard(qubit);
      } else if (*thetaPhase == phase::ZERO) {
        circuit.AddZRot(qubit, *phiPhase + *lambdaPhase);
      } else if (*phiPhase == phase::MINUS_PI_BY_2 &&
                 *lambdaPhase == phase::PI_BY_2) {
        circuit.AddXRot(qubit, *thetaPhase);
      } else {
        circuit.AddZRot(qubit, *lambdaPhase - phase::PI_BY_2);
        circuit.AddXRot(qubit, *thetaPhase);
        circuit.AddZRot(qubit, *phiPhase + phase::PI_BY_2);
      }
    } else {
      if (thetaPhase.has_value() && *thetaPhase == phase::ZERO) {
        if (phiPhase.has_value() && *phiPhase == phase::ZERO) {
          circuit.AddZPauliExp(qubit,
                               qasmtools::ast::object::clone(gate.lambda()));
        } else if (lambdaPhase.has_value() && *lambdaPhase == phase::ZERO) {
          circuit.AddZPauliExp(qubit,
                               qasmtools::ast::object::clone(gate.phi()));
        } else {
          circuit.AddZPauliExp(qubit, AddExprPhases(gate.phi(), gate.lambda()));
        }
      } else {
        if (lambdaPhase.has_value()) {
          circuit.AddZRot(qubit, *lambdaPhase - phase::PI_BY_2);
        } else {
          circuit.AddZPauliExp(qubit, SubtractPIByTwoFromPhase(gate.lambda()));
        }

        if (thetaPhase.has_value()) {
          circuit.AddXRot(qubit, *thetaPhase);
        } else {
          circuit.AddXPauliExp(qubit,
                               qasmtools::ast::object::clone(gate.theta()));
        }

        if (phiPhase.has_value()) {
          circuit.AddZRot(qubit, *phiPhase + phase::PI_BY_2);
        } else {
          circuit.AddZPauliExp(qubit, AddPIByTwoToPhase(gate.phi()));
        }
      }
    }
  }

  void visit(qasmtools::ast::CNOTGate &gate) override {
    const auto &control = gate.ctrl();
    const auto &target = gate.tgt();
    const auto &cOffset = control.offset();
    const auto &tOffset = target.offset();
    assert(cOffset.has_value() && tOffset.has_value());
    circuit.AddCNOTGate({control.var(), *cOffset}, {target.var(), *tOffset});
  }

 private:
  PauliCircuit &circuit;
};

}  // namespace

PauliCircuit::PauliCircuit(qasmtools::ast::Program &&program)
    : qubitManager(std::make_shared<QubitManager>()),
      tableau(program.qubits(), qubitManager),
      numQubits(program.qubits()) {
  NormaliseProgram(program);
  GateReader reader(*this);
  program.accept(reader);
  ProcessGates();
}

void PauliCircuit::PrintDAG() const {
  pauli_graph.Print();
  std::cout << std::endl;

  tableau.Print();
  std::cout << std::endl;
}

namespace {

PauliExponential CreatePauliExp(const phase::RationalPhase &phase,
                                int numQubits, int qubit1, PauliLetter letter1,
                                int qubit2 = -1, PauliLetter letter2 = I) {
  std::vector<PauliLetter> string(numQubits, I);
  string[qubit1] = letter1;
  if (qubit2 != -1) string[qubit2] = letter2;
  return PauliExponential(string, phase.ToExpr());
}

}  // namespace

std::vector<SimpleClifford> PauliCircuit::OptimiseCliffords(
    std::vector<SimpleGate> &gates) {
  std::vector<SimpleGate> newGates;
  std::vector<bool> activeQubits(numQubits, true);
  PauliDAG cliffordDAG;
  std::vector<PauliExponential> paulis;
  for (const auto &gate : gates) {
    if (std::holds_alternative<CliffordGate>(gate)) {
      const auto &clifford = std::get<CliffordGate>(gate);
      auto index1 = qubitManager->GetQubitIndex(clifford.GetFirstQubit());
      if (clifford.GetGateType() == CNOT) {
        auto index2 = qubitManager->GetQubitIndex(clifford.GetSecondQubit());
        if (!activeQubits[index1] || !activeQubits[index2]) {
          activeQubits[index1] = false;
          activeQubits[index2] = false;
          newGates.push_back(gate);
          continue;
        }
        // Add three pauli exps
        paulis.push_back(CreatePauliExp(phase::RationalPhase({-1, 2}),
                                        numQubits, index1, Z, index2, X));

        paulis.push_back(
            CreatePauliExp(phase::RationalPhase({1, 2}), numQubits, index1, Z));
        paulis.push_back(
            CreatePauliExp(phase::RationalPhase({1, 2}), numQubits, index2, X));
      } else {
        if (!activeQubits[index1]) {
          newGates.push_back(gate);
          continue;
        }
        if (clifford.GetGateType() == HAD) {
          paulis.push_back(CreatePauliExp(phase::RationalPhase({1, 2}),
                                          numQubits, index1, Z));
          paulis.push_back(CreatePauliExp(phase::RationalPhase({1, 2}),
                                          numQubits, index1, X));
          paulis.push_back(CreatePauliExp(phase::RationalPhase({1, 2}),
                                          numQubits, index1, Z));
          // Add three exponentials
        } else if (clifford.GetGateType() == ZROT) {
          paulis.push_back(
              CreatePauliExp(*clifford.GetPhase(), numQubits, index1, Z));
        } else {
          assert(clifford.GetGateType() == XROT);
          paulis.push_back(
              CreatePauliExp(*clifford.GetPhase(), numQubits, index1, X));
        }
      }
    } else {
      const auto &qubit = std::get<ZGate>(gate).GetQubit();
      auto index = qubitManager->GetQubitIndex(qubit);
      activeQubits[index] = false;
      newGates.push_back(gate);
    }
  }
  for (auto it = paulis.rbegin(); it != paulis.rend(); it++) {
    cliffordDAG.AddPauli(std::move(*it));
  }
  StabiliserTableau tableau(numQubits, qubitManager);
  cliffordDAG.ExhaustiveRunner(tableau);
  cliffordDAG.Reduce(tableau);
  gates = std::move(newGates);
  return cliffordDAG.SynthesiseCliffords(*qubitManager, numQubits);
}

void PauliCircuit::Synthesise(std::ostream &output) {
  output << "OPENQASM 2.0;" << std::endl;
  output << "include \"qelib1.inc\";" << std::endl;
  qubitManager->Synthesise(output);
  std::vector<SimpleGate> gates;
  tableau.Synthesise(gates);
  pauli_graph.Synthesise(gates, *qubitManager);
  auto cliffords = OptimiseCliffords(gates);
  for (const auto &clifford : cliffords) {
    if (std::holds_alternative<CliffordGate>(clifford)) {
      const auto &cnot = std::get<CliffordGate>(clifford);
      assert(cnot.GetGateType() == CNOT);
      cnot.Synthesise(output);
    } else {
      auto unitary = std::get<SingleQubitUnitary>(clifford);
      unitary.Synthesise(output);
    }
  }
  for (const auto &gate : gates) {
    if (std::holds_alternative<CliffordGate>(gate)) {
      std::get<CliffordGate>(gate).Synthesise(output);
    } else {
      std::get<ZGate>(gate).Synthesise(output);
    }
  }
}

size_t PauliCircuit::PauliCount() const { return pauli_graph.Size(); }

void PauliCircuit::Optimise() { pauli_graph.ExhaustiveRunner(tableau); }

void PauliCircuit::ProcessGates() {
  int nextIndex = FirstCliffordGate(0);
  int startIndex = 0;
  while (nextIndex != -1) {
    ShiftCliffordGate(startIndex, nextIndex);
    const auto &cliffordGate = std::get<CliffordGate>(gates[startIndex]);
    switch (cliffordGate.GetGateType()) {
      case GateType::HAD:
        tableau.ApplyHadamard(cliffordGate.GetFirstQubit());
        break;
      case GateType::CNOT:
        tableau.ApplyCNOTGate(cliffordGate.GetFirstQubit(),
                              cliffordGate.GetSecondQubit());
        break;
      case GateType::XROT:
        tableau.ApplyXRot(cliffordGate.GetFirstQubit(),
                          *cliffordGate.GetPhase());
        break;
      case GateType::ZROT:
        tableau.ApplyZRot(cliffordGate.GetFirstQubit(),
                          *cliffordGate.GetPhase());
        break;
      default:
        throw std::runtime_error("Unknown gate type");
    }
    startIndex++;
    nextIndex = FirstCliffordGate(nextIndex + 1);
  }

  for (int i{static_cast<int>(gates.size() - 1)}; i >= startIndex; i--) {
    pauli_graph.AddPauli(std::move(std::get<PauliExponential>(gates[i])));
  }
}

int PauliCircuit::FirstCliffordGate(int after) {
  for (int i{after}; i < gates.size(); i++) {
    if (std::holds_alternative<CliffordGate>(gates[i])) return i;
  }
  return -1;
}

void PauliCircuit::ShiftCliffordGate(int start, int clifford) {
  for (int i{clifford - 1}; i >= start; i--) {
    assert(std::holds_alternative<PauliExponential>(gates[i]));
    assert(std::holds_alternative<CliffordGate>(gates[i + 1]));
    auto pauli = std::move(std::get<PauliExponential>(gates[i]));
    auto clifford = std::move(std::get<CliffordGate>(gates[i + 1]));
    pauli.PushCliffordThrough(clifford, qubitManager);
    gates[i].emplace<CliffordGate>(std::move(clifford));
    gates[i + 1].emplace<PauliExponential>(std::move(pauli));
  }
}

void PauliCircuit::AddZPauliExp(const Qubit &qubit,
                                std::unique_ptr<qasmtools::ast::Expr> phase) {
  const int index = qubitManager->GetQubitIndex(qubit);
  std::vector<PauliLetter> pauliString(numQubits, PauliLetter::I);
  pauliString[index] = PauliLetter::Z;
  gates.push_back(PauliExponential(pauliString, std::move(phase)));
}

void PauliCircuit::AddXPauliExp(const Qubit &qubit,
                                std::unique_ptr<qasmtools::ast::Expr> phase) {
  const int index = qubitManager->GetQubitIndex(qubit);
  std::vector<PauliLetter> pauliString(numQubits, PauliLetter::I);
  pauliString[index] = PauliLetter::X;
  gates.push_back(PauliExponential(pauliString, std::move(phase)));
}

void PauliCircuit::AddHadamard(const Qubit &qubit) {
  gates.push_back(CliffordGate::CreateHAD(qubit));
}

void PauliCircuit::AddZRot(const Qubit &qubit,
                           const phase::RationalPhase &phase) {
  gates.push_back(CliffordGate::CreateZRot(qubit, phase));
}

void PauliCircuit::AddXRot(const Qubit &qubit,
                           const phase::RationalPhase &phase) {
  gates.push_back(CliffordGate::CreateXRot(qubit, phase));
}

void PauliCircuit::AddCNOTGate(const Qubit &control, const Qubit &target) {
  gates.push_back(CliffordGate::CreateCNOT(control, target));
}

void PauliCircuit::AddQubits(const std::string &name, int number) {
  qubitManager->AddQubits(name, number);
}

}  // namespace circuit
}  // namespace qstabr
