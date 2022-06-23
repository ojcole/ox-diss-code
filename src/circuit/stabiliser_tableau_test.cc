#include "stabiliser_tableau.h"

#include <gtest/gtest.h>

#include "qubit_manager.h"

#define QUBIT "qubit"

namespace {

using namespace qstabr;
using namespace circuit;

Qubit MkQubit(int num) { return {QUBIT, num}; }

TEST(CanCreate, AcceptsValid) {
  std::shared_ptr<circuit::QubitManager> manager =
      std::make_shared<circuit::QubitManager>();
  manager->AddQubits(QUBIT, 4);

  {
    circuit::StabiliserTableau tableau(4, manager);
    {
      auto canCreate = tableau.CanCreate("IIII"_p);
      EXPECT_TRUE(canCreate.has_value() && !*canCreate);
    }
    {
      auto canCreate = tableau.CanCreate("IIIZ"_p);
      EXPECT_TRUE(canCreate.has_value() && !*canCreate);
    }
    {
      auto canCreate = tableau.CanCreate("ZIIZ"_p);
      EXPECT_TRUE(canCreate.has_value() && !*canCreate);
    }
    {
      auto canCreate = tableau.CanCreate("ZIZZ"_p);
      EXPECT_TRUE(canCreate.has_value() && !*canCreate);
    }
    {
      auto canCreate = tableau.CanCreate("ZZZZ"_p);
      EXPECT_TRUE(canCreate.has_value() && !*canCreate);
    }
  }

  {
    circuit::StabiliserTableau tableau(4, manager);
    tableau.ApplyCNOTGate(MkQubit(0), MkQubit(1));
    tableau.ApplyHadamard(MkQubit(0));
    tableau.ApplyZRot(MkQubit(0), phase::Fraction{-1, 2});
    tableau.ApplyCNOTGate(MkQubit(1), MkQubit(3));
    tableau.ApplyHadamard(MkQubit(2));
    tableau.ApplyCNOTGate(MkQubit(2), MkQubit(1));
    tableau.Print();
    {
      auto canCreate = tableau.CanCreate("YYYI"_p);
      EXPECT_TRUE(canCreate.has_value() && *canCreate);
    }
    {
      auto canCreate = tableau.CanCreate("YZZZ"_p);
      EXPECT_TRUE(canCreate.has_value() && *canCreate);
    }
    {
      auto canCreate = tableau.CanCreate("IXXZ"_p);
      EXPECT_TRUE(canCreate.has_value() && !*canCreate);
    }
  }

  {
    circuit::StabiliserTableau tableau(4, manager);
    tableau.ApplyCNOTGate(MkQubit(0), MkQubit(1));
    tableau.ApplyCNOTGate(MkQubit(1), MkQubit(0));
    tableau.ApplyCNOTGate(MkQubit(0), MkQubit(1));
    tableau.Print();
    {
      auto canCreate = tableau.CanCreate("IIII"_p);
      EXPECT_TRUE(canCreate.has_value() && !*canCreate);
    }
    {
      auto canCreate = tableau.CanCreate("IIIZ"_p);
      EXPECT_TRUE(canCreate.has_value() && !*canCreate);
    }
    {
      auto canCreate = tableau.CanCreate("IZZI"_p);
      EXPECT_TRUE(canCreate.has_value() && !*canCreate);
    }
  }
}

TEST(CanCreate, RejectsInvalid) {
  std::shared_ptr<circuit::QubitManager> manager =
      std::make_shared<circuit::QubitManager>();
  manager->AddQubits(QUBIT, 4);

  {
    circuit::StabiliserTableau tableau(4, manager);
    {
      auto canCreate = tableau.CanCreate("IIIX"_p);
      EXPECT_FALSE(canCreate.has_value());
    }
    {
      auto canCreate = tableau.CanCreate("XIIX"_p);
      EXPECT_FALSE(canCreate.has_value());
    }
    {
      auto canCreate = tableau.CanCreate("YIXY"_p);
      EXPECT_FALSE(canCreate.has_value());
    }
    {
      auto canCreate = tableau.CanCreate("XXYX"_p);
      EXPECT_FALSE(canCreate.has_value());
    }
  }

  {
    circuit::StabiliserTableau tableau(4, manager);
    tableau.ApplyCNOTGate(MkQubit(0), MkQubit(1));
    tableau.ApplyHadamard(MkQubit(0));
    tableau.ApplyZRot(MkQubit(0), phase::Fraction{-1, 2});
    tableau.ApplyCNOTGate(MkQubit(1), MkQubit(3));
    tableau.ApplyHadamard(MkQubit(2));
    tableau.ApplyCNOTGate(MkQubit(2), MkQubit(1));
    tableau.Print();
    {
      auto canCreate = tableau.CanCreate("XXXZ"_p);
      EXPECT_FALSE(canCreate.has_value());
    }
  }
}

}  // namespace