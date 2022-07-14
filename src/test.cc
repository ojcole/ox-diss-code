#include <iostream>

#include "phase/phase.h"

using namespace qstabr;

const double EPSILON = 1e-6;
const double PI = 3.14159265359f;
const double PI2 = 1.57079632679f;

void norm(double& num) { num -= 2 * PI * std::round(num / (2 * PI)); }

bool isPi(double num) {
  norm(num);
  return std::abs(std::abs(num) - PI) < EPSILON;
}

int main(int argc, char const* argv[]) {
  double x = -3.14159274101257f;
  std::cout << isPi(x) << std::endl;
  norm(x);
  std::cout << x << std::endl;
  phase::RationalPhase phase({-1, 2});
  std::cout << (phase * -1) << std::endl;
}
