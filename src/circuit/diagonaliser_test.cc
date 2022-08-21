#include "diagonaliser.h"

#include <gtest/gtest.h>

#include "test_helpers.h"

namespace {

using namespace qstabr;
using namespace circuit;

TEST(Diagonalise, OnlyAffectsThosePassed) {
  int numQubits = 4;
  for (int i{}; i < 100; i++) {
    auto exponentials = RandomCommutingGroup(numQubits, 20);
    Diagonaliser diag(exponentials, numQubits);
    auto result = diag.Diagonalise({});
    ASSERT_EQ(result.size(), 0);
  }
}

TEST(Diagonalise, AlreadyDiagUnaffected) {
  int numQubits = 8;
  for (int i{}; i < 100; i++) {
    auto exponentials = RandomCommutingGroup(numQubits, 128, {Z, I});
    Diagonaliser diag(exponentials, numQubits);
    std::vector<int> all;
    for (const auto &p : exponentials) {
      all.push_back(p.first);
    }
    auto result = diag.Diagonalise(all);
    ASSERT_EQ(result.size(), 0);
  }
}

TEST(Diagonalise, RandomTests) {
  for (int numQubits = 2; numQubits < 20; numQubits++) {
    auto manager = std::make_shared<QubitManager>();
    manager->AddQubits("qubit", numQubits);
    for (int i{}; i < 100; i++) {
      auto exponentials = RandomCommutingGroup(numQubits, 1024);
      std::unordered_map<int, PauliExponential> copy;
      for (const auto &p : exponentials) {
        PauliExponential expCopy = {
            p.second.GetString(), qasmtools::ast::RealExpr::create(
                                      {}, *p.second.GetExpr().constant_eval())};
        copy.insert({p.first, std::move(expCopy)});
      }
      Diagonaliser diag(exponentials, numQubits);
      std::vector<int> all;
      for (const auto &p : exponentials) {
        all.push_back(p.first);
      }
      auto result = diag.Diagonalise(all);
      for (auto &p : exponentials) {
        std::cout << p.second.GetString() << std::endl;
        std::cout << copy.at(p.first).GetString() << std::endl;
        for (auto it = result.rbegin(); it != result.rend(); it++) {
          it->Synthesise(std::cout, *manager);
          p.second.PushCliffordThrough(it->Dagger());
        }
        std::cout << p.second.GetString() << std::endl;
        std::cout << copy.at(p.first).GetString() << std::endl;
        ASSERT_EQ(p.second.GetString(), copy.at(p.first).GetString());
        ASSERT_EQ(p.second.GetExpr().constant_eval(),
                  copy.at(p.first).GetExpr().constant_eval());
        ASSERT_EQ(p.second.IsNegated(), copy.at(p.first).IsNegated());
      }
    }
  }
}

}  // namespace