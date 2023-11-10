#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, PrintSub)
{
  rule_library_t lib = rule_library();
  for (auto it = lib.cases[kOptSub].begin(); it != lib.cases[kOptSub].end(); it++)
  {
    std::cout << it->first << std::endl;
  }
}

TEST(Sym, Number)
{
  symbol_t x = create_symbol("3");
  symbol_t y = create_symbol("2");
  symbol_t z = c_sub(x, y);
  EXPECT_EQ(compare(z, create_flt("1")), 0);

  x = create_symbol("x");
  y = create_symbol("y");
  z = c_sub(x, y);
  // std::cout << print_string(z) << std::endl;
  EXPECT_STREQ(print_string(z).c_str(), "x+-1*y");

  x = create_symbol("x");
  y = create_symbol("x");
  z = c_sub(x, y);
  // std::cout << print_string(z) << std::endl;
  EXPECT_STREQ(print_string(z).c_str(), "x+-1*x");
  z = sub(x, y);
  EXPECT_STREQ(print_string(z).c_str(), "0");
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}