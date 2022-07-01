#include <iostream>

#include "circuit/helpers.h"
#include "circuit/pauli_circuit.h"
#include "staq/qasmtools/parser/parser.hpp"

int main(int argc, char const* argv[]) {
  // auto ast = qasmtools::parser::parse_file("qasm_bench/medium/dnn_n8.qasm");
  // auto ast = qasmtools::parser::parse_file("qasm_files/h2.qasm");
  auto ast = qasmtools::parser::parse_file("qasm_files/test.qasm");
  // auto ast =
  //     qasmtools::parser::parse_file("tket_bench/h2/H2_cmplt_JW_ccpvdz.qasm");

  // qstabr::circuit::NormaliseProgram(*ast);
  qstabr::circuit::PauliCircuit circuit(std::move(*ast));
  // auto manager = std::make_shared<qstabr::circuit::QubitManager>();
  // qstabr::circuit::StabiliserTableau tableau(4, manager);
  // tableau.AddQubits("qubit", 4);

  // tableau.ApplyCNOTGate({"qubit", 0}, {"qubit", 1});
  // tableau.ApplyHadamard({"qubit", 0});
  // tableau.ApplyHadamard({"qubit", 3});
  // tableau.ApplyXRot({"qubit", 1}, qstabr::phase::RationalPhase({-1, 2}));
  // tableau.ApplyXRot({"qubit", 2}, qstabr::phase::RationalPhase({-1, 2}));
  // tableau.ApplyCNOTGate({"qubit", 2}, {"qubit", 0});
  // tableau.ApplyCNOTGate({"qubit", 0}, {"qubit", 2});
  // tableau.ApplyCNOTGate({"qubit", 2}, {"qubit", 0});
  // tableau.ApplyPhase({"qubit", 0});
  // tableau.ApplyHadamard({"qubit", 2});
  // tableau.ApplyHadamard({"qubit", 1});
  // tableau.ApplyCNOTGate({"qubit", 0}, {"qubit", 1});
  // tableau.ApplyCNOTGate({"qubit", 1}, {"qubit", 3});
  // tableau.ApplyCNOTGate({"qubit", 2}, {"qubit", 3});
  // tableau.ApplyHadamard({"qubit", 3});
  // tableau.ApplyPhase({"qubit", 1});

  std::ofstream stream("test.txt");
  // ast->pretty_print(stream);
  circuit.Synthesise(stream);
}
