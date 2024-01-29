#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/construct.h>

using namespace mysym;

TEST(Sym, MatchIn)
{
  symbol_t p1 = c_pow("x", create_int("3"));
  symbol_t p2 = c_pow("y", create_int("2"));
  symbol_t p3 = c_pow("x", create_int("4"));
  symbol_t p4 = c_pow("x", c_frac("1", "4"));
  symbol_t p5 = c_add(p3, p4);
  symbol_t p6 = c_add(p1, p2);
  symbol_t p7 = c_add(p5, p6);
  // std::cout << print_string(p7) << std::endl;
  symbol_t x = c_pow("x", create_int("4"));
  EXPECT_TRUE(match_in(x, p7));
  symbol_t y = c_pow("x", create_int("3"));
  EXPECT_TRUE(match_in(y, p7));
  symbol_t z = c_pow("x", c_frac("1", "4"));
  EXPECT_TRUE(match_in(z, p7));
  EXPECT_TRUE(match_in(create_var("x"), p7));
}

TEST(Sym, AbsMatchIn)
{
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}