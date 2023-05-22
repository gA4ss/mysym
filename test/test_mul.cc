#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, PrintMul)
{
  rule_library_t lib = rule_library();
  for (auto it = lib.cases[kOptMul].begin(); it != lib.cases[kOptMul].end(); it++)
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
  EXPECT_EQ(compare(mul(x, y), create_flt("4.71")), 0);

  x = c_frac("1", "2");
  y = create_flt("1.5");
  EXPECT_EQ(compare(mul(x, y), c_mul("1.5", c_frac("1", "2"))), 0);

  x = c_frac("1", "3");
  y = create_int("4");
  EXPECT_EQ(compare(mul(x, y), c_frac("4","3")), 0);

  x = gConstE;
  y = create_flt("1.5");
  EXPECT_STREQ(print_string(mul(x, y)).c_str(), "1.5*e");

  x = gConstE;
  y = gConstPI;
  EXPECT_STREQ(print_string(mul(x, y)).c_str(), "e*pi");

  x = gConstE;
  y = gConstInf;
  EXPECT_STREQ(print_string(mul(x, y)).c_str(), "inf");

  x = gConstE;
  y = gConstNegInf;
  EXPECT_STREQ(print_string(mul(x, y)).c_str(), "-inf");

  x = create_var("x");
  y = create_flt("1.5");
  EXPECT_STREQ(print_string(mul(x, y)).c_str(), "1.5*x");

  x = create_flt("3.1415");
  y = c_sin("y");
  EXPECT_STREQ(print_string(mul(x, y)).c_str(), "3.1415*sin(y)");
}

TEST(Sym, SymMul)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z1 = c_mul("z", "x");
  // std::cout << print_string(z1) << std::endl;
  symbol_t z2 = c_add("a", c_mul("x", "y"));
  // std::cout << print_string(z2) << std::endl;
  symbol_t z3 = mul(x, z1);
  std::cout << print_string(z3) << std::endl;
  symbol_t z4 = mul(x, z2);
  std::cout << print_string(z4) << std::endl;
  // EXPECT_EQ(compare(mul(x, y), create_flt("4.71")), 0);
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}