#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/wrapper.h>
#include <mysym/construct.h>

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
  symbol_t z = "-1" * x;
  EXPECT_STREQ(print_string(z).c_str(), "-1*x");
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
  EXPECT_EQ(compare(mul(x, y), c_frac("4", "3")), 0);

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

TEST(Sym, Pow)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z = c_add(x, y);
  symbol_t e1 = c_pow(z, "2");
  // std::cout << print_string(e1) << std::endl;
  EXPECT_STREQ(print_string(e1).c_str(), "(x+y)^2");
}

TEST(Sym, MutilMul)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t a = create_sym("a");
  symbol_t b = create_sym("b");

  symbol_t xy = x + y;
  symbol_t z = xy * xy;
  EXPECT_STREQ(print_string(z).c_str(), "x^2+y^2+2*x*y");

  symbol_t z1 = c_mul("z", "x");
  symbol_t z2 = c_mul("5", "a");

  symbol_t p = x * z1;
  EXPECT_STREQ(print_string(p).c_str(), "z*x^2");
  p = y * z1;
  EXPECT_STREQ(print_string(p).c_str(), "x*y*z");

  p = z1 * z2;
  EXPECT_STREQ(print_string(p).c_str(), "5*a*x*z");
  z1 = z1 * create_symbol("y");
  p = z1 * y;
  EXPECT_STREQ(print_string(p).c_str(), "x*z*y^2");

  z1 = x + b;
  z2 = y + a;
  p = z1 * z2;
  // std::cout << p << std::endl;
  EXPECT_STREQ(print_string(p).c_str(), "a*b+a*x+b*y+x*y");
  symbol_t p2 = p * x;
  // std::cout << p << std::endl;
  EXPECT_STREQ(print_string(p2).c_str(), "a*x^2+y*x^2+a*b*x+b*x*y");

  // z1 = p2 * x;
  // std::cout << z1 << std::endl;

  z1 = x * y;
  p = p2 * z1;
  // std::cout << p << std::endl;
  EXPECT_STREQ(print_string(p).c_str(), "x^3*y^2+a*y*x^3+b*x^2*y^2+a*b*y*x^2");
}

// TEST(Sym, Negative)
// {
//   symbol_t x = create_sym("x");
//   symbol_t y = create_sym("y");
//   symbol_t z = c_add(x, y);
//   symbol_t e = c_mul(z, "-1");
//   // std::cout << print_string(e) << std::endl;
//   EXPECT_STREQ(print_string(e).c_str(), "-1*x+-1*y");
// }

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}