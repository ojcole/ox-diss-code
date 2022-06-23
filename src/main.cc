#include <iostream>

#include "circuit/pauli_circuit.h"
#include "staq/qasmtools/parser/parser.hpp"

int main(int argc, char const* argv[]) {
  auto ast = qasmtools::parser::parse_file("qasm_bench/medium/dnn_n8.qasm");
  // auto ast = qasmtools::parser::parse_file("qasm_files/h2.qasm");

  qstabr::circuit::PauliCircuit circuit(std::move(*ast));
}
