#ifndef STABILISERS_STABILISER_TABLEAU_H
#define STABILISERS_STABILISER_TABLEAU_H

#include <string>
#include <unordered_map>

#include "phase/phase.h"
#include "staq/qasmtools/ast/ast.hpp"

namespace qstabr {
namespace stabiliser {

struct Qubit {
  const std::string name;
  const int offset;
};

class StabiliserTableau {
 public:
  StabiliserTableau(qasmtools::ast::Program &&program);

  void AddQubits(const std::string &name, int number);
  void ApplyUnitaryGate(const Qubit &qubit, const phase::RationalPhase &theta,
                        const phase::RationalPhase &phi,
                        const phase::RationalPhase &lambda);
  void ApplyZRot(const Qubit &qubit, const phase::RationalPhase &phase);
  void ApplyXRot(const Qubit &qubit, const phase::RationalPhase &phase);
  void ApplyHadamard(const Qubit &qubit);
  void ApplyCNOTGate(const Qubit &control, const Qubit &target);

  void Print();

 private:
  void NormaliseProgram(qasmtools::ast::Program &program);
  void GenerateTableau(qasmtools::ast::Program &normalisedProgram);
  int GetQubitIndex(const Qubit &qubit);

  struct QubitEntry {
    int size;
    int firstQubit;
  };

  int numQubits;
  int nextQubit = 0;
  std::unordered_map<std::string, QubitEntry> qubits;
  std::vector<std::vector<int>> grid;
};

}  // namespace stabiliser
}  // namespace qstabr

#endif
