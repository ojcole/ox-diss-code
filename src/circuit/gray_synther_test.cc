#include "gray_synther.h"

#include <gtest/gtest.h>

#include "test_helpers.h"

namespace {

using namespace qstabr;
using namespace circuit;

TEST(GraySynth, RandomisedTests) {
  for (int numQubits = 2; numQubits < 20; numQubits++) {
    for (int i{}; i < 100; i++) {
      auto exponentials = RandomCommutingGroup(numQubits, 1024, {Z, I});
      std::unordered_map<int, PauliExponential> copy;
      for (const auto &p : exponentials) {
        std::cout << p.second.GetString() << std::endl;
        PauliExponential expCopy = {
            p.second.GetString(), qasmtools::ast::RealExpr::create(
                                      {}, *p.second.GetExpr().constant_eval())};
        copy.insert({p.first, std::move(expCopy)});
      }
      GraySynther gray(exponentials, numQubits);
      std::vector<int> all;
      for (const auto &p : exponentials) {
        all.push_back(p.first);
      }
      std::vector<SimpleGate> result;
      gray.GraySynth(result, all);
      std::list<PauliExponential> newP;
      for (int i{}; i < static_cast<int>(result.size()); i++) {
        if (std::holds_alternative<ZGate>(result[i])) {
          auto &gate = std::get<ZGate>(result[i]);
          std::vector<PauliLetter> string(numQubits, I);
          string[gate.GetQubit()] = Z;
          newP.push_back(
              {string, qasmtools::ast::RealExpr::create({}, gate.GetAngle())});
        } else {
          auto &gate = std::get<CliffordGate>(result[i]);
          for (auto &p : newP) {
            p.PushCliffordThrough(gate);
          }
        }
      }
      for (const auto &p : copy) {
        auto &exp = p.second;
        bool found = false;
        for (auto it = newP.begin(); it != newP.end(); it++) {
          if (exp.GetString() == it->GetString()) {
            if (exp.IsNegated() == it->IsNegated()) {
              ASSERT_EQ(exp.GetExpr().constant_eval(),
                        it->GetExpr().constant_eval());
            } else {
              ASSERT_EQ(-1 * *exp.GetExpr().constant_eval(),
                        *it->GetExpr().constant_eval());
            }
            found = true;
            newP.erase(it);
            break;
          }
        }
        ASSERT_TRUE(found);
      }
    }
  }
}

}  // namespace