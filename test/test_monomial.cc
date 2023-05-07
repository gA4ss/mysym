#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Monomial)
{
  symbol_t s1 = c_add("x", "y"); // x + y
  EXPECT_FALSE(is_monomial(s1, create_var("x")));
  symbol_t s2 = c_add(create_var("z"), c_mul("a", "b")); // z + ab
  EXPECT_FALSE(is_monomial(s2, create_var("z")));
  symbol_t s3 = c_mul("a", "b");
  EXPECT_FALSE(is_monomial(s3, create_var("a")));
  symbol_t s4 = c_pow("a", create_int("5"));
  EXPECT_TRUE(is_monomial(s4, create_var("a")));
  symbol_t s5 = c_pow("a", create_int("5"));
  symbol_t s6 = c_pow("a", create_int("3"));
  symbol_t s7 = c_mul(s6, s5);
  EXPECT_TRUE(is_monomial(s7, create_var("a")));
}

TEST(Sym, MonomialGME)
{
  symbol_t s1 = c_add("x", "y"); // x + y
  EXPECT_FALSE(is_monomial(s1, {create_var("x"), create_var("y")}));
  symbol_t s2 = c_add(create_var("z"), c_mul("a", "b")); // z + ab
  EXPECT_FALSE(is_monomial(s2, {create_var("a"), create_var("b")}));
  symbol_t s3 = c_mul("a", "b");
  EXPECT_FALSE(is_monomial(s3, {create_var("c")}));
  symbol_t s4 = c_pow("a", create_int("5"));
  EXPECT_TRUE(is_monomial(s4, {create_var("a")}));
  symbol_t s5 = c_pow("a", create_int("5"));
  symbol_t s6 = c_pow("a", create_int("3"));
  symbol_t s7 = c_mul(s6, s6);
  EXPECT_TRUE(is_monomial(s7, {create_var("a"), create_var("b")}));
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}