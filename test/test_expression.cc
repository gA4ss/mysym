#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Expression) {
  symbol_t s1 = add("x", create_int("1"));
  symbol_t s2 = mul(create_sym("a"), s1);
  symbol_t s3 = mul(create_int("3"), cos("y"));
  symbol_t s4 = add(s2, s3);
  std::cout << print_string(s4) << std::endl;

  list_t l = complete_sub_expressions(s4);
  std::cout << print_string(l) << std::endl;
}

int main(int argc, char* argv[]) {
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}