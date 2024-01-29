#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/construct.h>

using namespace mysym;

TEST(Sym, Map) {
  symbol_t s1 = c_add("x", "y");   // x + y
  symbol_t s2 = c_add("z", c_mul("a", "b")); // z + ab
  // symbol_ptr_t s3 = add(s1, create_var("i"));

  symbol_t r = map(s1, s2);
  std::cout << print_string(r) << std::endl;

  r = map(s1, s2, kOptPow);
  std::cout << print_string(r) << std::endl;
}

int main(int argc, char* argv[]) {
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}