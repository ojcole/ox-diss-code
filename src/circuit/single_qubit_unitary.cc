#include "single_qubit_unitary.h"

namespace qstabr {
namespace circuit {

SingleQubitUnitary::SingleQubitUnitary(const Qubit &qubit)
    : qubit(qubit), alpha(0), beta(0), gamma(0) {}

void SingleQubitUnitary::AddZPhase(const phase::RationalPhase &phase) {
  gamma += phase;
}

void SingleQubitUnitary::AddXPhase(const phase::RationalPhase &phase) {
  if (phase == 0) return;
  if (phase == 1) {
    beta += 1;
    gamma *= -1;
    return;
  }

  if (beta == 0) {
    alpha = alpha + gamma;
    beta = phase;
    gamma = phase::RationalPhase(0);
    return;
  }

  if (beta == 1) {
    alpha -= gamma;
    beta = phase + 1;
    gamma = phase::RationalPhase(0);
    return;
  }

  alpha -= beta;
  beta = gamma - beta - phase;
  gamma = phase * -1;
}

void SingleQubitUnitary::ClearAlpha() {
  Simplify();
  alpha = phase::RationalPhase(0);
}

bool SingleQubitUnitary::CommutesPast(const PauliLetter letter) {
  if (letter == I) return true;
  Simplify();
  if (letter == Y) return alpha == 0 && beta == 0 && gamma == 0;
  if (letter == Z) return beta == 0;
  return alpha == 0 && gamma == 0;
}

void SingleQubitUnitary::Simplify() {
  if (beta == 1) {
    alpha -= gamma;
    gamma = phase::RationalPhase(0);
  }
  if (beta == 0) {
    alpha += gamma;
    gamma = phase::RationalPhase(0);
  }
}

const Qubit &SingleQubitUnitary::GetQubit() const { return qubit; }

void SingleQubitUnitary::Synthesise(std::ostream &output) {
  Simplify();
  if (alpha == 0 && beta == 0 && gamma == 0) return;
  output << "u3(" << beta << "," << (gamma - phase::PI_BY_2) << ","
         << (alpha + phase::PI_BY_2) << ") " << qubit << ";" << std::endl;
}

}  // namespace circuit
}  // namespace qstabr