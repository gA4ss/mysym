#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Expression) {
  symbol_t s1 = add("x", "y");   // x + y
  symbol_t s2 = add(create_sym("z"), mul("a", "b")); // z + ab
  // symbol_ptr_t s3 = add(s1, create_sym("i"));

  symbol_t r = map(s1, s2);
  std::cout << print_string(r) << std::endl;

  r = map(s1, s2, kOptSin);
  std::cout << print_string(r) << std::endl;
}

int main(int argc, char* argv[]) {
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}