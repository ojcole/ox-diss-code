#include <chrono>
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
  int threads = 1;
  if (argc >= 4) {
    try {
      threads = std::stoi(argv[3]);
    } catch (std::exception&) {
    }
  }

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

  auto start = std::chrono::high_resolution_clock::now();

  qstabr::circuit::PauliCircuit circuit(std::move(*ast));
  size_t beforeCount = circuit.PauliCount();
  circuit.Optimise(threads);
  size_t afterCount = circuit.PauliCount();
  auto stats = circuit.GetOptStats();

  if (argc >= 3) {
    std::string fileName(argv[2]);
    std::ofstream stream(fileName);
    circuit.Synthesise(stream, threads);
  } else {
    circuit.Synthesise(std::cout, threads);
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = end - start;
  auto totalMillis =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  auto seconds = totalMillis / 1000;
  auto millis = totalMillis % 1000;

  std::cout << group << "," << name << "," << beforeCount << "," << afterCount
            << "," << stats.identityMerges << "," << stats.totalMerges << ","
            << stats.phaseRemovals << "," << stats.cancellations << ","
            << stats.cliffordRemovals << "," << seconds << "." << millis
            << std::endl;
}
