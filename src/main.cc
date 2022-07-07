#include <iostream>

#include "circuit/helpers.h"
#include "circuit/pauli_circuit.h"
#include "staq/qasmtools/parser/parser.hpp"

int main(int argc, char const* argv[]) {
  if (argc < 2) {
    std::cerr << "Requires a file path argument" << std::endl;
    return 1;
  }
  auto ast = qasmtools::parser::parse_file(argv[1]);
  qstabr::circuit::PauliCircuit circuit(std::move(*ast));
  size_t beforeCount = circuit.PauliCount();
  circuit.Optimise();
  size_t afterCount = circuit.PauliCount();

  std::string fileName(argv[1]);
  std::string group;
  std::string name;

  int current = 0;
  int next = fileName.find("/", current);  // find if have any at all
  while (next != std::string::npos) {
    if (current == 0) {
      group = fileName.substr(current, next - current);
    }
    current = next + 1;
    next = fileName.find("/", current);
  }
  name = fileName.substr(current, fileName.size() - current);

  std::cout << group << "\t" << name << "\t" << beforeCount << "\t"
            << afterCount << std::endl;

  circuit.PrintDAG();
  std::ofstream stream("test.qasm");
  circuit.Synthesise(stream);
}
