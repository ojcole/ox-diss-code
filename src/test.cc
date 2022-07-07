#include <iostream>

#include "phase/phase.h"

using namespace qstabr;

int main(int argc, char const* argv[]) {
  phase::RationalPhase phase(1);
  std::cout << phase << std::endl;
  std::cout << (phase == phase::RationalPhase(1)) << std::endl;
  std::cout << (phase != phase::RationalPhase(1)) << std::endl;
}
