#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, List)
{
  symbol_t s1 = add("x", "y"); // x + y
  EXPECT_FALSE(is_monomial(s1, create_sym("x")));
  symbol_t s2 = add(create_sym("z"), mul("a", "b")); // z + ab
  EXPECT_FALSE(is_monomial(s2, create_sym("z")));
  symbol_t s3 = mul("a", "b");
  EXPECT_FALSE(is_monomial(s3, create_sym("a")));
  symbol_t s4 = pow("a", create_int("5"));
  EXPECT_TRUE(is_monomial(s4, create_sym("a")));
  symbol_t s5 = pow("a", create_int("5"));
  symbol_t s6 = pow("a", create_int("3"));
  symbol_t s7 = mul(s6, s7);
  EXPECT_TRUE(is_monomial(s7, create_sym("a")));
}

TEST(Sym, Set)
{
  symbol_t s1 = add("x", "y"); // x + y
  EXPECT_FALSE(is_monomial(s1, create_sym("x")));
  symbol_t s2 = add(create_sym("z"), mul("a", "b")); // z + ab
  EXPECT_FALSE(is_monomial(s2, create_sym("z")));
  symbol_t s3 = mul("a", "b");
  EXPECT_FALSE(is_monomial(s3, create_sym("a")));
  symbol_t s4 = pow("a", create_int("5"));
  EXPECT_TRUE(is_monomial(s4, create_sym("a")));
  symbol_t s5 = pow("a", create_int("5"));
  symbol_t s6 = pow("a", create_int("3"));
  symbol_t s7 = mul(s6, s7);
  EXPECT_TRUE(is_monomial(s7, create_sym("a")));
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}