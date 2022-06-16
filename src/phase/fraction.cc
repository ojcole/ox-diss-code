#include "fraction.h"

namespace {

int gcd(int num, int denom) {
  while (denom != 0) {
    int tmp = denom;
    denom = num % denom;
    num = tmp;
  }
  return num;
}

}  // namespace

namespace qstabr {
namespace phase {

Fraction::Fraction(int numerator, int denominator)
    : numerator(numerator), denominator(denominator) {
  Normalise();
}
Fraction::Fraction(int num) : numerator(num), denominator(1) {}

int Fraction::getNumerator() const { return numerator; }
int Fraction::getDenominator() const { return denominator; }

void Fraction::Normalise() {
  bool negated = (numerator < 0) != (denominator < 0);
  if (numerator < 0) numerator *= -1;
  if (denominator < 0) denominator *= -1;

  int fac = gcd(numerator, denominator);
  while (fac != 1) {
    numerator /= fac;
    denominator /= fac;
    fac = gcd(numerator, denominator);
  }

  if (negated) {
    numerator *= -1;
  }
}

}  // namespace phase
}  // namespace qstabr
