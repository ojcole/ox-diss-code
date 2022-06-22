#include "fraction.h"

#include <gtest/gtest.h>

namespace {

using namespace qstabr;

TEST(NormalisesCorrectly, FullConstructor) {
  {
    phase::Fraction fraction{8, 4};
    ASSERT_EQ(fraction.GetNumerator(), 2);
    ASSERT_EQ(fraction.GetDenominator(), 1);
  }
  {
    phase::Fraction fraction{7, 3};
    ASSERT_EQ(fraction.GetNumerator(), 7);
    ASSERT_EQ(fraction.GetDenominator(), 3);
  }
  {
    phase::Fraction fraction{21, 12};
    ASSERT_EQ(fraction.GetNumerator(), 7);
    ASSERT_EQ(fraction.GetDenominator(), 4);
  }
  {
    phase::Fraction fraction{-21, 12};
    ASSERT_EQ(fraction.GetNumerator(), -7);
    ASSERT_EQ(fraction.GetDenominator(), 4);
  }
  {
    phase::Fraction fraction{21, -12};
    ASSERT_EQ(fraction.GetNumerator(), -7);
    ASSERT_EQ(fraction.GetDenominator(), 4);
  }
  {
    phase::Fraction fraction{-21, -12};
    ASSERT_EQ(fraction.GetNumerator(), 7);
    ASSERT_EQ(fraction.GetDenominator(), 4);
  }
  {
    phase::Fraction fraction{0, 1};
    ASSERT_EQ(fraction.GetNumerator(), 0);
    ASSERT_EQ(fraction.GetDenominator(), 1);
  }
  {
    phase::Fraction fraction{0, 7};
    ASSERT_EQ(fraction.GetNumerator(), 0);
    ASSERT_EQ(fraction.GetDenominator(), 1);
  }
  {
    phase::Fraction fraction{0, -7};
    ASSERT_EQ(fraction.GetNumerator(), 0);
    ASSERT_EQ(fraction.GetDenominator(), 1);
  }
}

TEST(AdditionWorks, FullConstructor) {
  {
    phase::Fraction fraction1{1, 4};
    phase::Fraction fraction2{1, 4};
    ASSERT_EQ(fraction1 + fraction2, phase::Fraction({1, 2}));
  }
  {
    phase::Fraction fraction1{1, 4};
    phase::Fraction fraction2{-1, 4};
    ASSERT_EQ(fraction1 + fraction2, phase::Fraction({0, 1}));
  }
  {
    phase::Fraction fraction1{-1, 4};
    phase::Fraction fraction2{-1, 4};
    ASSERT_EQ(fraction1 + fraction2, phase::Fraction({-1, 2}));
  }
  {
    phase::Fraction fraction1{-1, 4};
    phase::Fraction fraction2{1, 4};
    ASSERT_EQ(fraction1 + fraction2, phase::Fraction({0, 1}));
  }
}

}  // namespace