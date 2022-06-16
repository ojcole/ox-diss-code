#ifndef PHASE_PHASE_H_
#define PHASE_PHASE_H_

#include <ostream>

#include "fraction.h"
#include "staq/qasmtools/ast/traversal.hpp"

namespace qstabr {
namespace phase {

class RationalPhase {
 public:
  RationalPhase(Fraction fraction);

  Fraction getFraction() const;

  bool IsClifford() const;

  explicit operator int() const { return static_cast<int>(fraction); }

  inline bool operator==(const RationalPhase &other) const;
  inline bool operator!=(const RationalPhase &other) const;

  inline void operator+=(const RationalPhase &other);
  inline void operator-=(const RationalPhase &other);
  inline void operator*=(const RationalPhase &other);
  inline void operator/=(const RationalPhase &other);

 private:
  Fraction fraction;

  void Normalise();

  friend inline RationalPhase operator+(const RationalPhase &phase1,
                                        const RationalPhase &phase2);
  friend inline RationalPhase operator-(const RationalPhase &phase1,
                                        const RationalPhase &phase2);
  friend inline RationalPhase operator*(const RationalPhase &phase1,
                                        const RationalPhase &phase2);
  friend inline RationalPhase operator/(const RationalPhase &phase1,
                                        const RationalPhase &phase2);
  friend inline std::ostream &operator<<(std::ostream &stream,
                                         const RationalPhase &phase);
};

inline bool RationalPhase::operator==(const RationalPhase &other) const {
  return fraction == other.fraction;
}
inline bool RationalPhase::operator!=(const RationalPhase &other) const {
  return fraction != other.fraction;
}

inline RationalPhase operator+(const RationalPhase &phase1,
                               const RationalPhase &phase2) {
  RationalPhase newPhase = phase1.fraction + phase2.fraction;
  newPhase.Normalise();
  return newPhase;
}

inline RationalPhase operator-(const RationalPhase &phase1,
                               const RationalPhase &phase2) {
  RationalPhase newPhase = phase1.fraction - phase2.fraction;
  newPhase.Normalise();
  return newPhase;
}

inline RationalPhase operator*(const RationalPhase &phase1,
                               const RationalPhase &phase2) {
  RationalPhase newPhase = phase1.fraction * phase2.fraction;
  newPhase.Normalise();
  return newPhase;
}

inline RationalPhase operator/(const RationalPhase &phase1,
                               const RationalPhase &phase2) {
  RationalPhase newPhase = phase1.fraction / phase2.fraction;
  newPhase.Normalise();
  return newPhase;
}

inline void RationalPhase::operator+=(const RationalPhase &other) {
  fraction += other.fraction;
  Normalise();
}
inline void RationalPhase::operator-=(const RationalPhase &other) {
  fraction -= other.fraction;
  Normalise();
}
inline void RationalPhase::operator*=(const RationalPhase &other) {
  fraction *= other.fraction;
  Normalise();
}
inline void RationalPhase::operator/=(const RationalPhase &other) {
  fraction /= other.fraction;
  Normalise();
}

inline std::ostream &operator<<(std::ostream &stream,
                                const RationalPhase &phase) {
  return stream << phase.fraction.getNumerator() << "*pi/"
                << phase.fraction.getDenominator();
}

const RationalPhase PI_BY_2{{1, 2}};

RationalPhase getRationalPhaseFromExpr(qasmtools::ast::Expr &expression);

}  // namespace phase
}  // namespace qstabr

#endif