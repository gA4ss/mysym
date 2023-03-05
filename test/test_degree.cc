#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Degree)
{
  symbol_t x = create_var("x");
  symbol_t y = create_var("y");
  symbol_t x3 = c_pow("x", create_int("3"));
  symbol_t y3 = c_pow("y", create_int("2"));
  symbol_t xpy = c_add(x3, y3);
  EXPECT_STREQ(print_string(degree(xpy, x)).c_str(), "3");
  EXPECT_STREQ(print_string(degree(create_int("5"), x)).c_str(), "0");
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}