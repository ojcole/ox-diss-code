#ifndef PHASE_PHASE_H_
#define PHASE_PHASE_H_

#include <ostream>

#include "staq/qasmtools/ast/traversal.hpp"

namespace qstabr {
namespace phase {

class RationalPhase {
 public:
  RationalPhase(bool negated = false, int numerator = 1, int denominator = 1);
  RationalPhase(int num);

  void negate();

  explicit operator int() const { return numerator / denominator; }

 private:
  int numerator;
  int denominator;

  void normalise();

  friend inline bool operator==(const RationalPhase &phase1,
                                const RationalPhase &phase2);
  friend inline RationalPhase operator+(const RationalPhase &phase1,
                                        const RationalPhase &phase2);
  friend inline RationalPhase operator-(const RationalPhase &phase1,
                                        const RationalPhase &phase2);
  friend inline RationalPhase operator*(const RationalPhase &phase1,
                                        const RationalPhase &phase2);
  friend inline RationalPhase operator/(const RationalPhase &phase1,
                                        const RationalPhase &phase2);
  friend inline void operator+=(RationalPhase &phase1,
                                const RationalPhase &phase2);
  friend inline void operator-=(RationalPhase &phase1,
                                const RationalPhase &phase2);
  friend inline void operator*=(RationalPhase &phase1,
                                const RationalPhase &phase2);
  friend inline void operator/=(RationalPhase &phase1,
                                const RationalPhase &phase2);
  friend inline std::ostream &operator<<(std::ostream &stream,
                                         const RationalPhase &phase);
};

inline bool operator==(const RationalPhase &phase1,
                       const RationalPhase &phase2) {
  return phase1.numerator == phase2.numerator &&
         phase1.denominator == phase2.denominator;
}

inline RationalPhase operator+(const RationalPhase &phase1,
                               const RationalPhase &phase2) {
  RationalPhase phase(phase1);
  phase += phase2;
  return phase;
}

inline RationalPhase operator-(const RationalPhase &phase1,
                               const RationalPhase &phase2) {
  RationalPhase phase(phase1);
  phase -= phase2;
  return phase;
}

inline RationalPhase operator*(const RationalPhase &phase1,
                               const RationalPhase &phase2) {
  RationalPhase phase(phase1);
  phase *= phase2;
  return phase;
}

inline RationalPhase operator/(const RationalPhase &phase1,
                               const RationalPhase &phase2) {
  RationalPhase phase(phase1);
  phase /= phase2;
  return phase;
}

inline void operator+=(RationalPhase &phase1, const RationalPhase &phase2) {
  phase1.numerator *= phase2.denominator;
  phase1.numerator += phase2.numerator * phase1.denominator;
  phase1.denominator *= phase2.denominator;
  phase1.normalise();
}

inline void operator-=(RationalPhase &phase1, const RationalPhase &phase2) {
  phase1.numerator *= phase2.denominator;
  phase1.numerator -= phase2.numerator * phase1.denominator;
  phase1.denominator *= phase2.denominator;
  phase1.normalise();
}

inline void operator*=(RationalPhase &phase1, const RationalPhase &phase2) {
  phase1.numerator *= phase2.numerator;
  phase1.denominator *= phase2.denominator;
  phase1.normalise();
}

inline void operator/=(RationalPhase &phase1, const RationalPhase &phase2) {
  phase1.numerator *= phase2.denominator;
  phase1.denominator *= phase2.numerator;
  phase1.normalise();
}

inline std::ostream &operator<<(std::ostream &stream,
                                const RationalPhase &phase) {
  return stream << phase.numerator << "/" << phase.denominator;
}

const RationalPhase PI_BY_2{false, 1, 2};

RationalPhase getPhaseFromExpr(qasmtools::ast::Expr &expression);

}  // namespace phase
}  // namespace qstabr

#endif