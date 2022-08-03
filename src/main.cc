#include <chrono>
#include <iostream>

#include "circuit/helpers.h"
#include "circuit/pauli_circuit.h"
#include "staq/qasmtools/parser/parser.hpp"

class NullStream : public std::ostream {
 public:
  NullStream() : std::ostream(nullptr) {}
  NullStream(const NullStream &) : std::ostream(nullptr) {}
};

template <class T>
const NullStream &operator<<(NullStream &&stream, const T &) {
  return stream;
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cerr << "Requires a file path argument" << std::endl;
    return 1;
  }
  auto ast = qasmtools::parser::parse_file(argv[1]);
  int threads = 1;
  if (argc >= 4) {
    try {
      threads = std::stoi(argv[3]);
    } catch (std::exception &) {
    }
  }

  bool includeWithout = false;
  if (argc >= 5 && std::string(argv[4]) == "true") {
    includeWithout = true;
  }

  std::string fileName(argv[1]);
  std::string group;
  std::string name;

  int current = 0;
  size_t next = fileName.find("/", current);  // find if have any at all
  while (next != std::string::npos) {
    if (current != 0 && group.size() == 0) {
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

  qstabr::circuit::SynthOptions options = {
    threads : threads,
    reduceStrings : true,
  };

  if (argc >= 3) {
    std::string fileName(argv[2]);
    std::ofstream stream(fileName);
    circuit.Synthesise(stream, options);
  } else {
    circuit.Synthesise(std::cout, options);
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = end - start;
  auto totalMillis =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  auto seconds = totalMillis / 1000;
  auto millis = totalMillis % 1000;

  auto withReduceStats = circuit.GetOptStats();
  auto withReduceGateStats = withReduceStats.GateStats;
  auto withReduceDAGStats = withReduceStats.DAGStats;

  std::cout << group << "," << name << "," << beforeCount << "," << afterCount
            << "," << withReduceDAGStats.identityMerges << ","
            << withReduceDAGStats.totalMerges << ","
            << withReduceDAGStats.phaseRemovals << ","
            << withReduceDAGStats.cancellations << ","
            << withReduceDAGStats.cliffordRemovals << ","
            << withReduceDAGStats.stringReductions << ","
            << withReduceGateStats.originalGateCount << ","
            << withReduceGateStats.originalCNOTCount << ",";

  if (includeWithout) {
    auto ast = qasmtools::parser::parse_file(argv[1]);
    qstabr::circuit::PauliCircuit circuit(std::move(*ast));

    circuit.Optimise(threads);
    qstabr::circuit::SynthOptions options2 = {
      threads : threads,
      reduceStrings : false,
    };
    NullStream devNull;
    circuit.Synthesise(devNull, options2);

    auto withoutReduceStats = circuit.GetOptStats();
    auto withoutReduceGateStats = withoutReduceStats.GateStats;

    std::cout << withoutReduceGateStats.resultingGateCount << ","
              << withoutReduceGateStats.resultingCNOTCount << ",";
  }

  std::cout << withReduceGateStats.resultingGateCount << ","
            << withReduceGateStats.resultingCNOTCount << "," << seconds << "."
            << millis << std::endl;
}
