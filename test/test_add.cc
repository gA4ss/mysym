#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, PrintAdd)
{
  rule_library_t lib = rule_library();
  for (auto it = lib.cases[kOptAdd].begin(); it != lib.cases[kOptAdd].end(); it++)
  {
    std::cout << it->first << std::endl;
  }
}

TEST(Sym, Number)
{
  //
  // 常数与变量比较
  //
  symbol_t x = create_symbol("3.14");
  symbol_t y = create_flt("1.5");
  EXPECT_EQ(compare(add(x, y), create_flt("4.64")), 0);

  x = c_frac("1", "2");
  y = create_flt("1.5");
  EXPECT_EQ(compare(add(x, y), create_int("2")), 0);

  x = gConstE;
  y = create_flt("1.5");
  EXPECT_STREQ(print_string(add(x, y)).c_str(), "1.5+e");

  x = create_var("x");
  y = create_flt("1.5");
  EXPECT_STREQ(print_string(add(x, y)).c_str(), "1.5+x");

  x = create_flt("3.1415");
  y = c_sin("y");
  EXPECT_STREQ(print_string(add(x, y)).c_str(), "3.1415+sin(y)");
}

TEST(Sym, Frac)
{
  //
  // 常数与变量比较
  //
  symbol_t x = c_frac("1", "4");
  symbol_t y = c_frac("1", "2");
  symbol_t z = add(x, y);
  EXPECT_EQ(compare(z, create_flt("0.75")), 0);

  x = gConstE;
  y = c_frac("1", "2");
  z = add(x, y);
  EXPECT_STREQ(print_string(z).c_str(), "1/2+e");
  EXPECT_EQ(compare(z, c_add("0.5", "e")), 0);

  // x = create_var("x");
  // y = create_flt("1.5");
  // EXPECT_STREQ(print_string(add(x, y)).c_str(), "1.5+x");

  // x = create_flt("3.1415");
  // y = c_sin("y");
  // EXPECT_STREQ(print_string(add(x, y)).c_str(), "3.1415+sin(y)");
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}