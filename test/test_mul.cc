#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/wrapper.h>

using namespace mysym;

// TEST(Sym, PrintMul)
// {
//   rule_library_t lib = rule_library();
//   for (auto it = lib.cases[kOptMul].begin(); it != lib.cases[kOptMul].end(); it++)
//   {
//     std::cout << it->first << std::endl;
//   }
// }

TEST(Sym, MulOne)
{
  //
  // 常数与变量比较
  //
  symbol_t x = create_symbol("x");
  symbol_t y = create_int("1");
  EXPECT_EQ(compare(x * y, x), 0);
  y = opposite(y);
  EXPECT_EQ(compare(x * y, opposite(x)), 0);
}

TEST(Sym, Number)
{
  //
  // 常数与变量比较
  //
  symbol_t x = create_symbol("3.14");
  symbol_t y = create_flt("1.5");
  symbol_t ans = mul(x, y);
  EXPECT_EQ(compare(ans, create_flt("4.71")), 0);

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
  symbol_t z2 = c_add("a", c_mul("x", "y"));
  symbol_t z3 = mul(x, z1);
  // std::cout << print_string(z3) << std::endl;
  EXPECT_STREQ(print_string(z3).c_str(), "z*x^2");
  symbol_t z4 = mul(x, z2);
  EXPECT_STREQ(print_string(z4).c_str(), "a*x+y*x^2");
  // std::cout << print_string(z4) << std::endl;
}

TEST(Sym, MutilMul)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z1 = c_mul("z", "x");
  symbol_t z2 = c_mul("5", "a");
  symbol_t z3 = c_add("a", c_mul("x", "y"));
  symbol_t z4 = c_add("5", "x");
  symbol_t k = mul(z1, z2);
  EXPECT_STREQ(print_string(k).c_str(), "5*a*x*z");
  // (a+x*y)*(5+x) = 5*a+5*x*y+a*x+y*^(x,2)
  k = mul(z3, z4);
  EXPECT_STREQ(print_string(k).c_str(), "5*a+5*x*y+a*x+y*x^2");
  // std::cout << print_string(k) << std::endl;
  // (x*z) * (a + x*y) = a*x*z + y*z*^(x,2)
  k = mul(z1, z3);
  EXPECT_STREQ(print_string(k).c_str(), "a*x*z+y*z*x^2");
  // std::cout << print_string(k) << std::endl;
}

TEST(Sym, Pow)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z = c_add(x, y);
  symbol_t e1 = c_pow(z, "2");
  // std::cout << print_string(e1) << std::endl;
  EXPECT_STREQ(print_string(e1).c_str(), "(x+y)^2");
}

TEST(Sym, Negative)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z = c_add(x, y);
  symbol_t e = c_mul(z, "-1");
  // std::cout << print_string(e) << std::endl;
  EXPECT_STREQ(print_string(e).c_str(), "-1*x+-1*y");
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}