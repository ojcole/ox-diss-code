#include "diagonaliser.h"

#include <algorithm>
#include <cassert>

namespace qstabr {
namespace circuit {

namespace {

CliffordGate GetConj(PauliLetter letter, int qubit) {
  assert(letter != I && letter != Z);
  if (letter == X) {
    return CliffordGate::CreateHAD(qubit);
  }
  assert(letter == Y);
  return CliffordGate::CreateXRot(qubit, phase::PI_BY_2);
}

}  // namespace

Diagonaliser::Diagonaliser(std::unordered_map<int, PauliExponential>& paulis,
                           std::shared_ptr<QubitManager> qubitManager)
    : paulis(paulis),
      qubitManager(std::move(qubitManager)),
      numQubits(qubitManager->GetNumQubits()) {}

void Diagonaliser::ResetState(const std::vector<int>& group) {
  this->group = group;
  qubits.clear();
  diagonalQubits.clear();
  conj.clear();
  for (int i{}; i < qubitManager->GetNumQubits(); i++) {
    bool diag = true;
    for (const auto pauliIndex : group) {
      const auto& pauli = paulis.at(pauliIndex);
      if (!pauli.DiagAtQubit(i)) {
        diag = false;
        break;
      }
    }
    if (diag) {
      diagonalQubits.insert(i);
    } else {
      qubits.push_back(i);
    }
  }
}

bool Diagonaliser::DiagonaliseTrivial(int qubit) {
  PauliLetter letter = I;
  bool success = true;

  for (auto pauliIndex : group) {
    const auto& pauliString = paulis.at(pauliIndex).GetString();
    if (pauliString[qubit] != letter) {
      if (letter != I) {
        success = false;
        break;
      } else {
        letter = pauliString[qubit];
      }
    }
  }

  if (!success) return false;

  if (letter != Z && letter != I) {
    for (auto pauliIndex : group) {
      paulis.at(pauliIndex).DiagonaliseQubit(qubit);
    }
    conj.push_back(GetConj(letter, qubit));
  }

  return true;
}

// A pair of qubits i,j is compatible iff there exists {A, B} s.t.
//  for all gadgets l,
//      gadget l on qubit i \in {I, A} iff gadget l on qubit j \in {I, B}

// const std::unordered_map<PauliLetter, PauliLetter>
// DIAG_BY_CNOT{{I, Z}, {X, Y}, {Y, X}, {Z, {I, Z}}};

void Diagonaliser::ConjugateForDiag(int qubit, PauliLetter letter) {
  if (letter != X && letter != Y) return;
  auto gate = letter == X ? CliffordGate::CreateHAD(qubit)
                          : CliffordGate::CreateXRot(qubit, phase::PI_BY_2);
  for (const auto pauliIndex : group) {
    paulis.at(pauliIndex).PushCliffordThrough(gate, *qubitManager);
  }
  conj.push_back(std::move(gate));
}

void Diagonaliser::DiagonaliseCompatible() {
  for (auto first_letter : ACTIVE_LETTERS) {
    for (auto second_letter : ACTIVE_LETTERS) {
      auto it = qubits.begin();
      while (it != qubits.end()) {
        int i = *it;
        auto j_it = it;
        j_it++;
        bool diagonalised = false;
        while (j_it != qubits.end()) {
          int j = *j_it;
          bool all = true;
          for (const auto pauliIndex : group) {
            const auto& pauliString = paulis.at(pauliIndex).GetString();
            auto i_let = pauliString[i];
            auto j_let = pauliString[j];

            if ((i_let == first_letter || i_let == I) !=
                (j_let == second_letter || j_let == I)) {
              all = false;
              break;
            }
          }
          if (all) {
            ConjugateForDiag(i, first_letter);
            ConjugateForDiag(j, second_letter);
            auto gate = CliffordGate::CreateCNOT(i, j);
            for (const auto pauliIndex : group) {
              paulis.at(pauliIndex).PushCliffordThrough(gate, *qubitManager);
            }
            conj.push_back(std::move(gate));
            diagonalQubits.insert(*j_it);
            j_it = qubits.erase(j_it);
            if (DiagonaliseTrivial(i)) {
              diagonalised = true;
              diagonalQubits.insert(*it);
              it = qubits.erase(it);
              break;
            }
          } else {
            j_it++;
          }
        }
        if (!diagonalised) it++;
      }
    }
  }
}

bool Diagonaliser::VerifyMinWeight(const std::vector<int>& weightings,
                                   const std::vector<int>& newWeightings) {
  if (weightings.size() != 0 && newWeightings.size() >= weightings.size()) {
    return false;
  }
  for (const auto qubit : newWeightings) {
    if (diagonalQubits.find(qubit) == diagonalQubits.end()) return true;
  }
  return false;
}

std::vector<int> Diagonaliser::DiagonaliseMinWeight() {
  std::vector<int> weightings;
  int minPauli = -1;
  for (const auto pauliIndex : group) {
    auto newWeightings = paulis.at(pauliIndex).GetString().Weight();
    if (VerifyMinWeight(weightings, newWeightings)) {
      weightings = newWeightings;
      minPauli = pauliIndex;
    }
  }
  assert(minPauli != -1);
  std::vector<SimpleGate> gates;
  auto& pauli = paulis.at(minPauli);
  pauli.Synthesise(gates, *qubitManager);
  assert(gates.size() > 1);
  for (size_t i{}; i < gates.size() / 2; i++) {
    assert(std::holds_alternative<CliffordGate>(gates[i]));
    auto& gate = std::get<CliffordGate>(gates[i]);
    for (const auto pauliIndex : group) {
      if (pauliIndex == minPauli) continue;
      paulis.at(pauliIndex).PushCliffordThrough(gate, *qubitManager);
    }
    conj.push_back(std::move(gate));
  }
  assert(std::holds_alternative<ZGate>(gates[gates.size() / 2]));
  auto gate = std::get<ZGate>(gates[gates.size() / 2]);
  int remainingQubit = gate.GetQubit();
  pauli.ReduceToZ(remainingQubit);
  return weightings;
}

std::vector<CliffordGate> Diagonaliser::Diagonalise(
    const std::vector<int>& group) {
  ResetState(group);
  for (int i{}; i < numQubits; i++) {
    if (DiagonaliseTrivial(i)) {
      diagonalQubits.insert(i);
    } else {
      qubits.push_back(i);
    }
  }

  DiagonaliseCompatible();

  while (!qubits.empty()) {
    auto altered = DiagonaliseMinWeight();
    for (const auto qubit : altered) {
      if (!DiagonaliseTrivial(qubit)) {
        if (diagonalQubits.find(qubit) != diagonalQubits.end()) {
          diagonalQubits.erase(qubit);
          qubits.push_back(qubit);
        }
      } else {
        if (diagonalQubits.find(qubit) == diagonalQubits.end()) {
          qubits.erase(std::find(qubits.begin(), qubits.end(), qubit));
          diagonalQubits.insert(qubit);
        }
      }
    }
    DiagonaliseCompatible();
  }

  return std::move(conj);
}

}  // namespace circuit
}  // namespace qstabr