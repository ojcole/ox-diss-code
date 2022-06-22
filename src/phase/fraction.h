#ifndef PHASE_FRACTION_H_
#define PHASE_FRACTION_H_

#include <ostream>

namespace qstabr {
namespace phase {

class Fraction {
 public:
  Fraction(int numerator, int denominator);
  Fraction(int num);

  explicit operator int() const { return numerator / denominator; }

  int GetNumerator() const;
  int GetDenominator() const;

  inline bool operator==(const Fraction &other) const;
  inline bool operator!=(const Fraction &other) const;

  inline void operator+=(const Fraction &other);
  inline void operator-=(const Fraction &other);
  inline void operator*=(const Fraction &other);
  inline void operator/=(const Fraction &other);

 private:
  void Normalise();

  int numerator;
  int denominator;

  friend inline Fraction operator+(const Fraction &fraction1,
                                   const Fraction &fraction2);
  friend inline Fraction operator-(const Fraction &fraction1,
                                   const Fraction &fraction2);
  friend inline Fraction operator*(const Fraction &fraction1,
                                   const Fraction &fraction2);
  friend inline Fraction operator/(const Fraction &fraction1,
                                   const Fraction &fraction2);
  friend inline std::ostream &operator<<(std::ostream &stream,
                                         const Fraction &fraction);
};

inline bool Fraction::operator==(const Fraction &other) const {
  return numerator == other.numerator && denominator == other.denominator;
}

inline bool Fraction::operator!=(const Fraction &other) const {
  return numerator != other.numerator || denominator != other.denominator;
}

inline Fraction operator+(const Fraction &fraction1,
                          const Fraction &fraction2) {
  Fraction copy(fraction1);
  copy += fraction2;
  return copy;
}

inline Fraction operator-(const Fraction &fraction1,
                          const Fraction &fraction2) {
  Fraction copy(fraction1);
  copy -= fraction2;
  return copy;
}

inline Fraction operator*(const Fraction &fraction1,
                          const Fraction &fraction2) {
  Fraction copy(fraction1);
  copy *= fraction2;
  return copy;
}

inline Fraction operator/(const Fraction &fraction1,
                          const Fraction &fraction2) {
  Fraction copy(fraction1);
  copy /= fraction2;
  return copy;
}

inline void Fraction::operator+=(const Fraction &other) {
  numerator *= other.denominator;
  numerator += other.numerator * denominator;
  denominator *= other.denominator;
  Normalise();
}

inline void Fraction::operator-=(const Fraction &other) {
  numerator *= other.denominator;
  numerator -= other.numerator * denominator;
  denominator *= other.denominator;
  Normalise();
}

inline void Fraction::operator*=(const Fraction &other) {
  numerator *= other.numerator;
  denominator *= other.denominator;
  Normalise();
}

inline void Fraction::operator/=(const Fraction &other) {
  numerator *= other.denominator;
  denominator *= other.numerator;
  Normalise();
}

inline std::ostream &operator<<(std::ostream &stream,
                                const Fraction &fraction) {
  return stream << fraction.numerator << "/" << fraction.denominator;
}

}  // namespace phase
}  // namespace qstabr

#endif