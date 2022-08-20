#ifndef CIRCUIT_TEST_HELPERS_H_
#define CIRCUIT_TEST_HELPERS_H_

#include <random>
#include <vector>

#include "pauli_exponential.h"

const std::vector<qstabr::circuit::PauliLetter> ALL_LETTERS = {
    qstabr::circuit::I, qstabr::circuit::Z, qstabr::circuit::X,
    qstabr::circuit::Y};

qstabr::circuit::PauliExponential RandomPauliExp(
    int qubits,
    const std::vector<qstabr::circuit::PauliLetter> &pool = ALL_LETTERS) {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<size_t> distribution(0, pool.size() - 1);

  std::vector<qstabr::circuit::PauliLetter> pauliString;

  for (int i{}; i < qubits; i++) {
    auto letter = distribution(rng);
    pauliString.push_back(pool[letter]);
  }

  return {pauliString, qasmtools::ast::RealExpr::create({}, 0.3234)};
}

std::unordered_map<int, qstabr::circuit::PauliExponential> RandomCommutingGroup(
    int qubits, int iters,
    const std::vector<qstabr::circuit::PauliLetter> &pool = ALL_LETTERS) {
  std::unordered_map<int, qstabr::circuit::PauliExponential> group;
  int num = 0;
  for (int i{}; i < iters; i++) {
    auto exp = RandomPauliExp(qubits, pool);
    bool allI = true;
    for (int j{}; j < qubits; j++) {
      if (exp.GetString()[j] != qstabr::circuit::I) {
        allI = false;
        break;
      }
    }
    if (allI) continue;
    bool commutesAll = true;
    for (const auto &p : group) {
      if (!exp.CommutesWith(p.second) ||
          exp.GetString() == p.second.GetString()) {
        commutesAll = false;
        break;
      }
    }
    if (!commutesAll) continue;
    group.insert({num, std::move(exp)});
    num++;
  }
  return group;
}

#endif