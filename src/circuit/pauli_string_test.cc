#include "pauli_string.h"

#include <gtest/gtest.h>

#include "test_helpers.h"

namespace {

using namespace qstabr;
using namespace circuit;

TEST(Commutes, ExhaustiveTwoQubit) {
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("II"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("IZ"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("IX"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("IY"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("ZI"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("XI"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("YI"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("ZZ"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("ZX"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("ZY"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("XZ"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("XX"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("XY"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("YZ"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("YX"_p));
  ASSERT_TRUE(PauliString("II"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("IZ"_p).CommutesWith("IZ"_p));
  ASSERT_FALSE(PauliString("IZ"_p).CommutesWith("IX"_p));
  ASSERT_FALSE(PauliString("IZ"_p).CommutesWith("IY"_p));
  ASSERT_TRUE(PauliString("IZ"_p).CommutesWith("ZI"_p));
  ASSERT_TRUE(PauliString("IZ"_p).CommutesWith("XI"_p));
  ASSERT_TRUE(PauliString("IZ"_p).CommutesWith("YI"_p));
  ASSERT_TRUE(PauliString("IZ"_p).CommutesWith("ZZ"_p));
  ASSERT_FALSE(PauliString("IZ"_p).CommutesWith("ZX"_p));
  ASSERT_FALSE(PauliString("IZ"_p).CommutesWith("ZY"_p));
  ASSERT_TRUE(PauliString("IZ"_p).CommutesWith("XZ"_p));
  ASSERT_FALSE(PauliString("IZ"_p).CommutesWith("XX"_p));
  ASSERT_FALSE(PauliString("IZ"_p).CommutesWith("XY"_p));
  ASSERT_TRUE(PauliString("IZ"_p).CommutesWith("YZ"_p));
  ASSERT_FALSE(PauliString("IZ"_p).CommutesWith("YX"_p));
  ASSERT_FALSE(PauliString("IZ"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("IX"_p).CommutesWith("IX"_p));
  ASSERT_FALSE(PauliString("IX"_p).CommutesWith("IY"_p));
  ASSERT_TRUE(PauliString("IX"_p).CommutesWith("ZI"_p));
  ASSERT_TRUE(PauliString("IX"_p).CommutesWith("XI"_p));
  ASSERT_TRUE(PauliString("IX"_p).CommutesWith("YI"_p));
  ASSERT_FALSE(PauliString("IX"_p).CommutesWith("ZZ"_p));
  ASSERT_TRUE(PauliString("IX"_p).CommutesWith("ZX"_p));
  ASSERT_FALSE(PauliString("IX"_p).CommutesWith("ZY"_p));
  ASSERT_FALSE(PauliString("IX"_p).CommutesWith("XZ"_p));
  ASSERT_TRUE(PauliString("IX"_p).CommutesWith("XX"_p));
  ASSERT_FALSE(PauliString("IX"_p).CommutesWith("XY"_p));
  ASSERT_FALSE(PauliString("IX"_p).CommutesWith("YZ"_p));
  ASSERT_TRUE(PauliString("IX"_p).CommutesWith("YX"_p));
  ASSERT_FALSE(PauliString("IX"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("IY"_p).CommutesWith("IY"_p));
  ASSERT_TRUE(PauliString("IY"_p).CommutesWith("ZI"_p));
  ASSERT_TRUE(PauliString("IY"_p).CommutesWith("XI"_p));
  ASSERT_TRUE(PauliString("IY"_p).CommutesWith("YI"_p));
  ASSERT_FALSE(PauliString("IY"_p).CommutesWith("ZZ"_p));
  ASSERT_FALSE(PauliString("IY"_p).CommutesWith("ZX"_p));
  ASSERT_TRUE(PauliString("IY"_p).CommutesWith("ZY"_p));
  ASSERT_FALSE(PauliString("IY"_p).CommutesWith("XZ"_p));
  ASSERT_FALSE(PauliString("IY"_p).CommutesWith("XX"_p));
  ASSERT_TRUE(PauliString("IY"_p).CommutesWith("XY"_p));
  ASSERT_FALSE(PauliString("IY"_p).CommutesWith("YZ"_p));
  ASSERT_FALSE(PauliString("IY"_p).CommutesWith("YX"_p));
  ASSERT_TRUE(PauliString("IY"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("ZI"_p).CommutesWith("ZI"_p));
  ASSERT_FALSE(PauliString("ZI"_p).CommutesWith("XI"_p));
  ASSERT_FALSE(PauliString("ZI"_p).CommutesWith("YI"_p));
  ASSERT_TRUE(PauliString("ZI"_p).CommutesWith("ZZ"_p));
  ASSERT_TRUE(PauliString("ZI"_p).CommutesWith("ZX"_p));
  ASSERT_TRUE(PauliString("ZI"_p).CommutesWith("ZY"_p));
  ASSERT_FALSE(PauliString("ZI"_p).CommutesWith("XZ"_p));
  ASSERT_FALSE(PauliString("ZI"_p).CommutesWith("XX"_p));
  ASSERT_FALSE(PauliString("ZI"_p).CommutesWith("XY"_p));
  ASSERT_FALSE(PauliString("ZI"_p).CommutesWith("YZ"_p));
  ASSERT_FALSE(PauliString("ZI"_p).CommutesWith("YX"_p));
  ASSERT_FALSE(PauliString("ZI"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("XI"_p).CommutesWith("XI"_p));
  ASSERT_FALSE(PauliString("XI"_p).CommutesWith("YI"_p));
  ASSERT_FALSE(PauliString("XI"_p).CommutesWith("ZZ"_p));
  ASSERT_FALSE(PauliString("XI"_p).CommutesWith("ZX"_p));
  ASSERT_FALSE(PauliString("XI"_p).CommutesWith("ZY"_p));
  ASSERT_TRUE(PauliString("XI"_p).CommutesWith("XZ"_p));
  ASSERT_TRUE(PauliString("XI"_p).CommutesWith("XX"_p));
  ASSERT_TRUE(PauliString("XI"_p).CommutesWith("XY"_p));
  ASSERT_FALSE(PauliString("XI"_p).CommutesWith("YZ"_p));
  ASSERT_FALSE(PauliString("XI"_p).CommutesWith("YX"_p));
  ASSERT_FALSE(PauliString("XI"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("YI"_p).CommutesWith("YI"_p));
  ASSERT_FALSE(PauliString("YI"_p).CommutesWith("ZZ"_p));
  ASSERT_FALSE(PauliString("YI"_p).CommutesWith("ZX"_p));
  ASSERT_FALSE(PauliString("YI"_p).CommutesWith("ZY"_p));
  ASSERT_FALSE(PauliString("YI"_p).CommutesWith("XZ"_p));
  ASSERT_FALSE(PauliString("YI"_p).CommutesWith("XX"_p));
  ASSERT_FALSE(PauliString("YI"_p).CommutesWith("XY"_p));
  ASSERT_TRUE(PauliString("YI"_p).CommutesWith("YZ"_p));
  ASSERT_TRUE(PauliString("YI"_p).CommutesWith("YX"_p));
  ASSERT_TRUE(PauliString("YI"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("ZZ"_p).CommutesWith("ZZ"_p));
  ASSERT_FALSE(PauliString("ZZ"_p).CommutesWith("ZX"_p));
  ASSERT_FALSE(PauliString("ZZ"_p).CommutesWith("ZY"_p));
  ASSERT_FALSE(PauliString("ZZ"_p).CommutesWith("XZ"_p));
  ASSERT_TRUE(PauliString("ZZ"_p).CommutesWith("XX"_p));
  ASSERT_TRUE(PauliString("ZZ"_p).CommutesWith("XY"_p));
  ASSERT_FALSE(PauliString("ZZ"_p).CommutesWith("YZ"_p));
  ASSERT_TRUE(PauliString("ZZ"_p).CommutesWith("YX"_p));
  ASSERT_TRUE(PauliString("ZZ"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("ZX"_p).CommutesWith("ZX"_p));
  ASSERT_FALSE(PauliString("ZX"_p).CommutesWith("ZY"_p));
  ASSERT_TRUE(PauliString("ZX"_p).CommutesWith("XZ"_p));
  ASSERT_FALSE(PauliString("ZX"_p).CommutesWith("XX"_p));
  ASSERT_TRUE(PauliString("ZX"_p).CommutesWith("XY"_p));
  ASSERT_TRUE(PauliString("ZX"_p).CommutesWith("YZ"_p));
  ASSERT_FALSE(PauliString("ZX"_p).CommutesWith("YX"_p));
  ASSERT_TRUE(PauliString("ZX"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("ZY"_p).CommutesWith("ZY"_p));
  ASSERT_TRUE(PauliString("ZY"_p).CommutesWith("XZ"_p));
  ASSERT_TRUE(PauliString("ZY"_p).CommutesWith("XX"_p));
  ASSERT_FALSE(PauliString("ZY"_p).CommutesWith("XY"_p));
  ASSERT_TRUE(PauliString("ZY"_p).CommutesWith("YZ"_p));
  ASSERT_TRUE(PauliString("ZY"_p).CommutesWith("YX"_p));
  ASSERT_FALSE(PauliString("ZY"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("XZ"_p).CommutesWith("XZ"_p));
  ASSERT_FALSE(PauliString("XZ"_p).CommutesWith("XX"_p));
  ASSERT_FALSE(PauliString("XZ"_p).CommutesWith("XY"_p));
  ASSERT_FALSE(PauliString("XZ"_p).CommutesWith("YZ"_p));
  ASSERT_TRUE(PauliString("XZ"_p).CommutesWith("YX"_p));
  ASSERT_TRUE(PauliString("XZ"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("XX"_p).CommutesWith("XX"_p));
  ASSERT_FALSE(PauliString("XX"_p).CommutesWith("XY"_p));
  ASSERT_TRUE(PauliString("XX"_p).CommutesWith("YZ"_p));
  ASSERT_FALSE(PauliString("XX"_p).CommutesWith("YX"_p));
  ASSERT_TRUE(PauliString("XX"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("XY"_p).CommutesWith("XY"_p));
  ASSERT_TRUE(PauliString("XY"_p).CommutesWith("YZ"_p));
  ASSERT_TRUE(PauliString("XY"_p).CommutesWith("YX"_p));
  ASSERT_FALSE(PauliString("XY"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("YZ"_p).CommutesWith("YZ"_p));
  ASSERT_FALSE(PauliString("YZ"_p).CommutesWith("YX"_p));
  ASSERT_FALSE(PauliString("YZ"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("YX"_p).CommutesWith("YX"_p));
  ASSERT_FALSE(PauliString("YX"_p).CommutesWith("YY"_p));

  ASSERT_TRUE(PauliString("YY"_p).CommutesWith("YY"_p));
}

TEST(Product, ExhaustiveTwoQubit) {
  for (auto let11 : ALL_LETTERS) {
    for (auto let12 : ALL_LETTERS) {
      for (auto let21 : ALL_LETTERS) {
        for (auto let22 : ALL_LETTERS) {
          const PauliString string1{{let11, let12}};
          const PauliString string2{{let21, let22}};
          if (!string1.CommutesWith(string2)) return;
          auto product = string1 * string2;
          std::vector<PauliLetter> result;
          bool sign = false;
          int iCount = 0;
          if (string1[0] == string2[0]) {
            result.push_back(I);
          } else if (string1[0] == I) {
            result.push_back(string2[0]);
          } else if (string2[0] == I) {
            result.push_back(string1[0]);
          } else if (string1[0] == Z) {
            if (string2[0] == X) {
              iCount++;
              result.push_back(Y);
            } else {
              iCount++;
              sign = !sign;
              result.push_back(X);
            }
          } else if (string1[0] == X) {
            if (string2[0] == Z) {
              iCount++;
              sign = !sign;
              result.push_back(Y);
            } else {
              iCount++;
              result.push_back(Z);
            }
          } else if (string1[0] == Y) {
            if (string2[0] == Z) {
              iCount++;
              result.push_back(X);
            } else {
              iCount++;
              sign = !sign;
              result.push_back(Z);
            }
          }

          if (string1[1] == string2[1]) {
            result.push_back(I);
          } else if (string1[1] == I) {
            result.push_back(string2[1]);
          } else if (string2[1] == I) {
            result.push_back(string1[1]);
          } else if (string1[1] == Z) {
            if (string2[1] == X) {
              iCount++;
              result.push_back(Y);
            } else {
              iCount++;
              sign = !sign;
              result.push_back(X);
            }
          } else if (string1[1] == X) {
            if (string2[1] == Z) {
              iCount++;
              sign = !sign;
              result.push_back(Y);
            } else {
              iCount++;
              result.push_back(Z);
            }
          } else if (string1[1] == Y) {
            if (string2[1] == Z) {
              iCount++;
              result.push_back(X);
            } else {
              iCount++;
              sign = !sign;
              result.push_back(Z);
            }
          }

          if (iCount == 2) sign = !sign;

          PauliString resultString{result, sign};

          ASSERT_EQ(resultString, product);
          ASSERT_EQ(resultString.IsNegated(), product.IsNegated());
        }
      }
    }
  }
}

TEST(Product, RandomTests) {
  for (int numQubits{}; numQubits < 20; numQubits++) {
    for (int i{}; i < 1000; i++) {
      auto str1 = RandomPauliString(numQubits);
      auto str2 = RandomPauliString(numQubits);

      if (!str1.CommutesWith(str2)) continue;

      auto prod1 = str1 * str2;
      auto prod2 = str2 * str1;

      ASSERT_EQ(prod1, prod2);
      ASSERT_EQ(prod1.IsNegated(), prod2.IsNegated());
    }
  }
}

}  // namespace