#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/construct.h>

using namespace mysym;

TEST(Sym, Pow)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z = create_sym("z");

  symbol_t _x = c_mul("-1", "x");
  EXPECT_STREQ(print_string(_x).c_str(), "-1*x");
  EXPECT_STREQ(print_string(abs(_x)).c_str(), "x");

  symbol_t _y = c_mul("-1", c_mul("-1", c_mul(y, z)));
  EXPECT_STREQ(print_string(_y).c_str(), "y*z");
  EXPECT_STREQ(print_string(abs(_y)).c_str(), "abs(y*z)");

  symbol_t n = create_int("-5");
  EXPECT_STREQ(print_string(abs(n)).c_str(), "5");
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}