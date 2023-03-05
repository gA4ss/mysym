#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Coefficient)
{
  symbol_t x = create_var("x");
  symbol_t y = create_var("y");
  symbol_t x3 = c_pow("x", create_int("3"));
  x3 = c_mul(create_int("2"), x3);
  symbol_t y3 = c_pow("y", create_int("2"));
  y3 = c_mul(create_int("6"), y3);
  symbol_t xpy = c_add(x3, y3);
  xpy = c_add(xpy, create_int("9"));
  EXPECT_STREQ(print_string(coefficient(xpy, x, create_int("3"))).c_str(), "2");
  EXPECT_STREQ(print_string(coefficient(xpy, x, create_int("0"))).c_str(), "9");
  EXPECT_STREQ(print_string(coefficient(xpy, y, create_int("2"))).c_str(), "6");
  EXPECT_STREQ(print_string(coefficient(xpy, y, create_int("0"))).c_str(), "9");
  EXPECT_STREQ(print_string(coefficient(xpy, y, create_int("3"))).c_str(), "none");
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}