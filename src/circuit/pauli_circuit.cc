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
    gateCount++;

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
        if (*lambdaPhase != phase::PI_BY_2) {
          circuit.AddZRot(qubit, *lambdaPhase - phase::PI_BY_2);
        }
        circuit.AddXRot(qubit, *thetaPhase);
        if (*phiPhase != phase::MINUS_PI_BY_2) {
          circuit.AddZRot(qubit, *phiPhase + phase::PI_BY_2);
        }
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
    CNOTCount++;
    gateCount++;

    const auto &control = gate.ctrl();
    const auto &target = gate.tgt();
    const auto &cOffset = control.offset();
    const auto &tOffset = target.offset();
    assert(cOffset.has_value() && tOffset.has_value());
    circuit.AddCNOTGate({control.var(), *cOffset}, {target.var(), *tOffset});
  }

  int GetGateCount() const { return gateCount; }
  int GetCNOTCount() const { return CNOTCount; }

 private:
  PauliCircuit &circuit;
  int gateCount{};
  int CNOTCount{};
};

PauliExponential CreatePauliExp(const phase::RationalPhase &phase,
                                int numQubits, int qubit1, PauliLetter letter1,
                                int qubit2 = -1, PauliLetter letter2 = I) {
  std::vector<PauliLetter> string(numQubits, I);
  string[qubit1] = letter1;
  if (qubit2 != -1) string[qubit2] = letter2;
  return PauliExponential(string, phase.ToExpr());
}

inline void AddCNOTPauliExponential(std::vector<PauliExponential> &paulis,
                                    int numQubits, int index1, int index2) {
  paulis.push_back(CreatePauliExp(phase::RationalPhase({-1, 2}), numQubits,
                                  index1, Z, index2, X));
  paulis.push_back(
      CreatePauliExp(phase::RationalPhase({1, 2}), numQubits, index1, Z));
  paulis.push_back(
      CreatePauliExp(phase::RationalPhase({1, 2}), numQubits, index2, X));
}

inline void AddHADPauliExponential(std::vector<PauliExponential> &paulis,
                                   int numQubits, int index1) {
  paulis.push_back(
      CreatePauliExp(phase::RationalPhase({1, 2}), numQubits, index1, Z));
  paulis.push_back(
      CreatePauliExp(phase::RationalPhase({1, 2}), numQubits, index1, X));
  paulis.push_back(
      CreatePauliExp(phase::RationalPhase({1, 2}), numQubits, index1, Z));
}

inline void AddZRotPauliExponential(std::vector<PauliExponential> &paulis,
                                    int numQubits, int index1,
                                    const phase::RationalPhase &phase) {
  paulis.push_back(CreatePauliExp(phase, numQubits, index1, Z));
}

inline void AddXRotPauliExponential(std::vector<PauliExponential> &paulis,
                                    int numQubits, int index1,
                                    const phase::RationalPhase &phase) {
  paulis.push_back(CreatePauliExp(phase, numQubits, index1, X));
}

inline std::vector<PauliExponential> CliffordToPaulis(
    const CliffordGate &clifford, int numQubits) {
  std::vector<PauliExponential> paulis;
  int index1 = clifford.GetFirstQubit();
  if (clifford.GetGateType() == CNOT) {
    int index2 = clifford.GetSecondQubit();
    AddCNOTPauliExponential(paulis, numQubits, index1, index2);
  } else if (clifford.GetGateType() == HAD) {
    AddHADPauliExponential(paulis, numQubits, index1);
  } else if (clifford.GetGateType() == ZROT) {
    AddZRotPauliExponential(paulis, numQubits, index1, *clifford.GetPhase());
  } else {
    assert(clifford.GetGateType() == XROT);
    AddXRotPauliExponential(paulis, numQubits, index1, *clifford.GetPhase());
  }

  return paulis;
}

}  // namespace

PauliCircuit::PauliCircuit(qasmtools::ast::Program &&program)
    : qubitManager(std::make_shared<QubitManager>()),
      tableau(program.qubits(), qubitManager),
      pauli_graph(program.qubits()),
      numQubits(program.qubits()) {
  NormaliseProgram(program);
  GateReader reader(*this);
  program.accept(reader);
  originalGateCount = reader.GetGateCount();
  originalCNOTCount = reader.GetCNOTCount();
  ProcessGates3();
}

void PauliCircuit::PrintDAG() const {
  pauli_graph.Print();
  std::cout << std::endl;

  tableau.Print();
  std::cout << std::endl;
}

std::vector<SimpleClifford> PauliCircuit::OptimiseCliffords(
    std::vector<SimpleGate> &gates, int threads) const {
  std::vector<SimpleGate> newGates;
  std::vector<bool> activeQubits(numQubits, true);
  PauliDAG cliffordDAG(numQubits);
  std::vector<PauliExponential> paulis;
  for (const auto &gate : gates) {
    if (std::holds_alternative<CliffordGate>(gate)) {
      const auto &clifford = std::get<CliffordGate>(gate);
      auto index1 = clifford.GetFirstQubit();
      if (clifford.GetGateType() == CNOT) {
        auto index2 = clifford.GetSecondQubit();
        if (!activeQubits[index1] || !activeQubits[index2]) {
          activeQubits[index1] = false;
          activeQubits[index2] = false;
          newGates.push_back(gate);
          continue;
        }
        AddCNOTPauliExponential(paulis, numQubits, index1, index2);
      } else {
        if (!activeQubits[index1]) {
          newGates.push_back(gate);
          continue;
        }
        if (clifford.GetGateType() == HAD) {
          AddHADPauliExponential(paulis, numQubits, index1);
        } else if (clifford.GetGateType() == ZROT) {
          AddZRotPauliExponential(paulis, numQubits, index1,
                                  *clifford.GetPhase());
        } else {
          assert(clifford.GetGateType() == XROT);
          AddXRotPauliExponential(paulis, numQubits, index1,
                                  *clifford.GetPhase());
        }
      }
    } else {
      const auto qubit = std::get<ZGate>(gate).GetQubit();
      activeQubits[qubit] = false;
      newGates.push_back(gate);
    }
  }
  for (auto it = paulis.rbegin(); it != paulis.rend(); it++) {
    cliffordDAG.AddPauli(std::move(*it));
  }
  StabiliserTableau tableau(numQubits, qubitManager);
  bool repeat = false;
  std::vector<bool> qubitPis(numQubits, false);
  do {
    if (threads > 1) {
      cliffordDAG.ExhaustiveRunnerParallel(tableau, threads);
    } else {
      cliffordDAG.ExhaustiveRunner(tableau);
    }
    auto cliffords = cliffordDAG.PullOutPis();
    repeat = cliffords.size() > 0;
    for (const auto &clifford : cliffords) {
      assert(clifford.GetGateType() == XROT || clifford.GetGateType() == ZROT);
      if (clifford.GetGateType() == XROT) {
        auto phase = clifford.GetPhase();
        assert(phase.has_value());
        assert(*phase == phase::RationalPhase(1));
        auto qubit = clifford.GetFirstQubit();
        qubitPis[qubit] = !qubitPis[qubit];
        tableau.ApplyXRot(clifford.GetFirstQubit(), *phase);
      }
      // ZROTs just get ignored by tableau since kappas pop through
    }
  } while (repeat);
  gates = std::move(newGates);
  return cliffordDAG.SynthesiseCliffords(qubitPis);
}

void PauliCircuit::Synthesise(std::ostream &output,
                              const SynthOptions &options) {
  output << "OPENQASM 2.0;" << std::endl;
  output << "include \"qelib1.inc\";" << std::endl;
  qubitManager->Synthesise(output);
  std::vector<SimpleGate> gates;
  auto stabilisers = tableau.GetStabilisers();
  tableau.Synthesise(gates);
  pauli_graph.Synthesise(gates, stabilisers, options);
  auto cliffords = OptimiseCliffords(gates, options.threads);
  for (const auto &clifford : cliffords) {
    if (std::holds_alternative<CliffordGate>(clifford)) {
      const auto &cnot = std::get<CliffordGate>(clifford);
      assert(cnot.GetGateType() == CNOT);
      cnot.Synthesise(output, *qubitManager);
      resultingCNOTCount++;
      resultingGateCount++;
    } else {
      auto unitary = std::get<SingleQubitUnitary>(clifford);
      if (!unitary.Simplify()) {
        resultingGateCount++;
      }
      unitary.Synthesise(output, *qubitManager);
    }
  }
  for (const auto &gate : gates) {
    if (std::holds_alternative<CliffordGate>(gate)) {
      const auto &clifford = std::get<CliffordGate>(gate);
      if (clifford.GetGateType() == CNOT) {
        resultingCNOTCount++;
      }
      clifford.Synthesise(output, *qubitManager);
    } else {
      std::get<ZGate>(gate).Synthesise(output, *qubitManager);
    }
    resultingGateCount++;
  }
}

size_t PauliCircuit::PauliCount() const { return pauli_graph.Size(); }

PauliCircuit::FullStats PauliCircuit::GetOptStats() const {
  GateOptStats stats = {
    originalGateCount : originalGateCount,
    originalCNOTCount : originalCNOTCount,
    resultingGateCount : resultingGateCount,
    resultingCNOTCount : resultingCNOTCount,
  };
  return {stats, pauli_graph.GetStats()};
}

void PauliCircuit::Optimise(int threads) {
  bool repeat = false;
  do {
    if (threads > 1) {
      pauli_graph.ExhaustiveRunnerParallel(tableau, threads);
    } else {
      pauli_graph.ExhaustiveRunner(tableau);
    }
    auto cliffords = pauli_graph.PullOutCliffords();
    repeat = cliffords.size() > 0;
    for (const auto &clifford : cliffords) {
      tableau.ApplyCliffordGate(clifford);
    }
    if (repeat) ReconstructDAG(pauli_graph);
  } while (repeat);
}

void PauliCircuit::ReconstructDAG(PauliDAG &dag) const {
  auto paulis = dag.GetPaulis();
  for (auto it = paulis.rbegin(); it != paulis.rend(); it++) {
    dag.AddPauli(std::move(*it));
  }
}

void PauliCircuit::ProcessGates() {
  std::vector<int> cliffords;
  for (int i = static_cast<int>(gates.size() - 1); i >= 0; i--) {
    if (std::holds_alternative<CliffordGate>(gates[i])) {
      cliffords.push_back(i);
    } else {
      auto &pauli = std::get<PauliExponential>(gates[i]);
      for (auto it = cliffords.rbegin(); it != cliffords.rend(); it++) {
        const auto &cliffordGate = std::get<CliffordGate>(gates[*it]);
        pauli.PushCliffordThrough(cliffordGate);
      }
      pauli_graph.AddPauli(std::move(pauli));
    }
  }
  for (auto it = cliffords.rbegin(); it != cliffords.rend(); it++) {
    tableau.ApplyCliffordGate(std::get<CliffordGate>(gates[*it]));
  }
}

void PauliCircuit::ProcessGates2() {
  for (auto it = gates.rbegin(); it != gates.rend(); it++) {
    if (std::holds_alternative<CliffordGate>(*it)) {
      auto paulis =
          CliffordToPaulis(std::move(std::get<CliffordGate>(*it)), numQubits);
      for (auto pauliIt = paulis.rbegin(); pauliIt != paulis.rend();
           pauliIt++) {
        tableau.ShiftPauliExponential(*pauliIt);
        tableau.ApplyCliffordPauliExponential(*pauliIt);
      }
    } else {
      auto &pauli = std::get<PauliExponential>(*it);
      tableau.ShiftPauliExponential(pauli);
      pauli_graph.AddPauli(std::move(pauli));
    }
  }
}

void PauliCircuit::ProcessGates3() {
  size_t cutOff = numQubits * numQubits * 35;
  std::vector<int> cliffords;
  int i = static_cast<int>(gates.size() - 1);
  for (; i >= 0; i--) {
    if (std::holds_alternative<CliffordGate>(gates[i])) {
      cliffords.push_back(i);
      if (cliffords.size() > cutOff) {
        i--;
        break;
      }
    } else {
      auto &pauli = std::get<PauliExponential>(gates[i]);
      for (auto it = cliffords.rbegin(); it != cliffords.rend(); it++) {
        const auto &cliffordGate = std::get<CliffordGate>(gates[*it]);
        pauli.PushCliffordThrough(cliffordGate);
      }
      pauli_graph.AddPauli(std::move(pauli));
    }
  }

  for (auto it = cliffords.rbegin(); it != cliffords.rend(); it++) {
    tableau.ApplyCliffordGate(std::get<CliffordGate>(gates[*it]));
  }
  for (; i >= 0; i--) {
    auto &gate = gates[i];
    if (std::holds_alternative<CliffordGate>(gate)) {
      auto paulis =
          CliffordToPaulis(std::move(std::get<CliffordGate>(gate)), numQubits);
      for (auto pauliIt = paulis.rbegin(); pauliIt != paulis.rend();
           pauliIt++) {
        tableau.ShiftPauliExponential(*pauliIt);
        tableau.ApplyCliffordPauliExponential(*pauliIt);
      }
    } else {
      auto &pauli = std::get<PauliExponential>(gate);
      tableau.ShiftPauliExponential(pauli);
      pauli_graph.AddPauli(std::move(pauli));
    }
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
  gates.push_back(CliffordGate::CreateHAD(qubitManager->GetQubitIndex(qubit)));
}

void PauliCircuit::AddZRot(const Qubit &qubit,
                           const phase::RationalPhase &phase) {
  gates.push_back(
      CliffordGate::CreateZRot(qubitManager->GetQubitIndex(qubit), phase));
}

void PauliCircuit::AddXRot(const Qubit &qubit,
                           const phase::RationalPhase &phase) {
  gates.push_back(
      CliffordGate::CreateXRot(qubitManager->GetQubitIndex(qubit), phase));
}

void PauliCircuit::AddCNOTGate(const Qubit &control, const Qubit &target) {
  gates.push_back(
      CliffordGate::CreateCNOT(qubitManager->GetQubitIndex(control),
                               qubitManager->GetQubitIndex(target)));
}

void PauliCircuit::AddQubits(const std::string &name, int number) {
  qubitManager->AddQubits(name, number);
}

}  // namespace circuit
}  // namespace qstabr
