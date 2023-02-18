#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Polynomial) {
  symbol_t s1 = add("x", create_int("3"));   // x + y
  EXPECT_TRUE(is_polynomial(s1, create_sym("x")));
  symbol_t s2 = add(create_sym("z"), mul(create_int("5"), "z")); // z + ab
  EXPECT_TRUE(is_polynomial(s2, create_sym("z")));
  symbol_t s3 = mul(create_int("5"), "b");
  EXPECT_TRUE(is_polynomial(s3, create_sym("b")));
  symbol_t s4 = pow(mul("a", "b"), create_int("5"));
  EXPECT_FALSE(is_polynomial(s4, create_sym("b")));
  symbol_t s5 = pow("a", create_int("5"));
  symbol_t s6 = pow("a", create_int("3"));
  symbol_t s7 = add(s6,s7);
  EXPECT_TRUE(is_polynomial(s7, create_sym("a")));
}

int main(int argc, char* argv[]) {
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}