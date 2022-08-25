#include <chrono>
#include <iostream>

#include "circuit/helpers.h"
#include "circuit/pauli_circuit.h"
#include "staq/qasmtools/parser/parser.hpp"

namespace {

class GateReader : public qasmtools::ast::Traverse {
 public:
  GateReader() {}

  void visit(qasmtools::ast::RegisterDecl &reg) override {
    if (reg.is_quantum()) {
      qubitManager.AddQubits(reg.id(), reg.size());
      for (int i{}; i < reg.size(); i++) {
        tDepth.push_back(0);
        cxDepth.push_back(0);
        gateDepth.push_back(0);
      }
    }
  }

  void visit(qasmtools::ast::UGate &gate) override {
    const auto &arg = gate.arg();
    const auto &offset = arg.offset();
    auto qubit = qubitManager.GetQubitIndex({arg.var(), *offset});

    auto theta =
        qstabr::circuit::CliffordPhaseFromDouble(*gate.theta().constant_eval());
    auto phi =
        qstabr::circuit::CliffordPhaseFromDouble(*gate.phi().constant_eval());
    auto lambda = qstabr::circuit::CliffordPhaseFromDouble(
        *gate.lambda().constant_eval());

    bool isClifford =
        theta.has_value() && phi.has_value() && lambda.has_value();
    if (!isClifford) {
      tDepth[qubit]++;
    }
    gateDepth[qubit]++;
  }

  void visit(qasmtools::ast::CNOTGate &gate) override {
    const auto &control = gate.ctrl();
    const auto &target = gate.tgt();
    const auto &cOffset = control.offset();
    const auto &tOffset = target.offset();
    auto controlQubit = qubitManager.GetQubitIndex({control.var(), *cOffset});
    auto targetQubit = qubitManager.GetQubitIndex({target.var(), *tOffset});

    cxDepth[controlQubit] =
        std::max(cxDepth[controlQubit], cxDepth[targetQubit]);
    cxDepth[targetQubit] = cxDepth[controlQubit];

    tDepth[controlQubit] = std::max(tDepth[controlQubit], tDepth[targetQubit]);
    tDepth[targetQubit] = tDepth[controlQubit];

    gateDepth[controlQubit] =
        std::max(gateDepth[controlQubit], gateDepth[targetQubit]);
    gateDepth[targetQubit] = gateDepth[controlQubit];

    cxDepth[controlQubit]++;
    cxDepth[targetQubit]++;

    gateDepth[controlQubit]++;
    gateDepth[targetQubit]++;
  }

  int GetTDepth() {
    int maxDepth{};
    for (const auto depth : tDepth) {
      maxDepth = std::max(depth, maxDepth);
    }
    return maxDepth;
  }

  int GetCXDepth() {
    int maxDepth{};
    for (const auto depth : cxDepth) {
      maxDepth = std::max(depth, maxDepth);
    }
    return maxDepth;
  }

  int GetGateDepth() {
    int maxDepth{};
    for (const auto depth : gateDepth) {
      maxDepth = std::max(depth, maxDepth);
    }
    return maxDepth;
  }

 private:
  qstabr::circuit::QubitManager qubitManager;
  std::vector<int> tDepth;
  std::vector<int> cxDepth;
  std::vector<int> gateDepth;
};

struct DepthStats {
  int tDepth;
  int cxDepth;
  int gateDepth;
};

DepthStats GetDepthStats(std::string filename) {
  auto ast = qasmtools::parser::parse_file(filename);

  qstabr::circuit::NormaliseProgram(*ast);

  GateReader reader;
  ast->accept(reader);

  return {
    tDepth : reader.GetTDepth(),
    cxDepth : reader.GetCXDepth(),
    gateDepth : reader.GetGateDepth()
  };
}

}  // namespace

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
  auto beforeDepthStats = GetDepthStats(argv[1]);
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

  DepthStats afterDepthStats{};
  if (argc >= 3) {
    afterDepthStats = GetDepthStats(argv[2]);
  }

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
            << withReduceGateStats.originalCNOTCount << ","
            << beforeDepthStats.gateDepth << "," << beforeDepthStats.cxDepth
            << "," << beforeDepthStats.tDepth << ",";

  if (includeWithout) {
    auto ast = qasmtools::parser::parse_file(argv[1]);
    qstabr::circuit::PauliCircuit circuit(std::move(*ast));

    circuit.Optimise(threads);
    qstabr::circuit::SynthOptions options2 = {
      threads : threads,
      reduceStrings : false,
    };

    DepthStats afterStatsWithout{};

    if (argc >= 3) {
      std::string fileName(argv[2]);
      {
        std::ofstream stream(fileName);
        circuit.Synthesise(stream, options2);
      }
      afterStatsWithout = GetDepthStats(fileName);
    } else {
      NullStream devNull;
      circuit.Synthesise(devNull, options2);
    }

    auto withoutReduceStats = circuit.GetOptStats();
    auto withoutReduceGateStats = withoutReduceStats.GateStats;

    std::cout << withoutReduceGateStats.resultingGateCount << ","
              << withoutReduceGateStats.resultingCNOTCount << ","
              << afterStatsWithout.gateDepth << "," << afterStatsWithout.cxDepth
              << "," << afterStatsWithout.tDepth << ",";
  }

  std::cout << withReduceGateStats.resultingGateCount << ","
            << withReduceGateStats.resultingCNOTCount << ","
            << afterDepthStats.gateDepth << "," << afterDepthStats.cxDepth
            << "," << afterDepthStats.tDepth << "," << seconds << "." << millis
            << std::endl;
}
