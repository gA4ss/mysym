#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Base)
{
  symbol_t x = create_var("x");
  EXPECT_STREQ(print_string(base(x)).c_str(), "x");

  symbol_t und = create_none();
  EXPECT_STREQ(print_string(base(und)).c_str(), "none");

  symbol_t p1 = c_pow("y", create_int("3"));
  EXPECT_STREQ(print_string(base(p1)).c_str(), "y");

  symbol_t p2 = c_pow(c_sin("x"), create_int("2"));
  EXPECT_STREQ(print_string(base(p2)).c_str(), "sin(x)");
}

TEST(Sym, Exponent)
{
  symbol_t x = create_var("x");
  EXPECT_STREQ(print_string(exponent(x)).c_str(), "1");

  symbol_t und = create_none();
  EXPECT_STREQ(print_string(base(und)).c_str(), "none");

  symbol_t p1 = c_pow("y", create_int("3"));
  EXPECT_STREQ(print_string(exponent(p1)).c_str(), "3");

  symbol_t p2 = c_pow(c_sin("x"), create_int("2"));
  EXPECT_STREQ(print_string(exponent(p2)).c_str(), "2");
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}