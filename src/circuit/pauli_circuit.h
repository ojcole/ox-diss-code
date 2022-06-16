#ifndef CIRCUIT_PAULI_CIRCUIT_H_
#define CIRCUIT_PAULI_CIRCUIT_H_

#include <variant>
#include <vector>

#include "clifford_gate.h"
#include "pauli.h"
#include "pauli_dag.h"
#include "stabiliser_tableau.h"
#include "staq/qasmtools/ast/program.hpp"

namespace qstabr {
namespace circuit {

class PauliCircuit {
 public:
  using Gate = std::variant<CliffordGate, PauliExponential>;

  PauliCircuit(qasmtools::ast::Program &program);

 private:
  void ProcessGates(const std::vector<Gate> &gates);

  StabiliserTableau tableau;
  PauliDAG pauli_graph;
};

}  // namespace circuit
}  // namespace qstabr

#endif