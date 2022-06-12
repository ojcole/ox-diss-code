#include <iostream>

#include "stabilisers/stabiliser_tableau.h"
#include "staq/qasmtools/parser/parser.hpp"

int main(int argc, char const* argv[]) {
  qasmtools::parser::Preprocessor preprocessor;
  preprocessor.add_target_file("qasm_files/clifford.qasm");

  qasmtools::parser::Parser parser(preprocessor);
  auto ast = parser.parse();

  qstabr::stabiliser::StabiliserTableau tableau(std::move(*ast));
  tableau.Print();
}
