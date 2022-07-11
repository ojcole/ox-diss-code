#include <iostream>

#include "circuit/stabiliser_tableau.h"
#include "staq/qasmtools/parser/parser.hpp"

using namespace qstabr;

int main(int argc, char const* argv[]) {
  if (argc < 3) {
    std::cerr << "Requires two file path arguments" << std::endl;
    return 1;
  }
  auto ast1 = qasmtools::parser::parse_file(argv[1]);
  auto ast2 = qasmtools::parser::parse_file(argv[2]);

  circuit::StabiliserTableau tableau1(std::move(*ast1));
  circuit::StabiliserTableau tableau2(std::move(*ast2));

  std::cout << std::boolalpha << (tableau1 == tableau2) << std::endl;

  tableau1.Print();
  std::cout << std::endl;
  tableau2.Print();
}
