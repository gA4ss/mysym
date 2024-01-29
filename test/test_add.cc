#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/construct.h>
#include <mysym/wrapper.h>

using namespace mysym;

// TEST(Sym, PrintAdd)
// {
//   rule_library_t lib = rule_library();
//   for (auto it = lib.cases[kOptAdd].begin(); it != lib.cases[kOptAdd].end(); it++)
//   {
//     std::cout << it->first << std::endl;
//   }
// }

TEST(Sym, Number)
{
  //
  // 常数与变量比较
  //
  symbol_t x = gConstInf;
  symbol_t y = gConstNegInf;
  EXPECT_EQ(compare(add(x, y), gConstZero), 0);

  x = create_symbol("3.14");
  y = create_flt("1.5");
  EXPECT_EQ(compare(add(x, y), create_flt("4.64")), 0);

  x = create_symbol("-3.14");
  y = create_flt("1.5");
  EXPECT_EQ(compare(add(x, y), create_flt("-1.64")), 0);

  x = create_symbol("5.3");
  y = create_flt("-0.3");
  EXPECT_EQ(compare(add(x, y), create_flt("5")), 0);

  x = c_frac("1", "2");
  y = create_flt("1.5");
  EXPECT_EQ(compare(add(x, y), c_add("1.5", x)), 0);

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
  EXPECT_STREQ(print_string(z).c_str(), "1//2+e");
  EXPECT_EQ(compare(z, c_add("0.5", "e")), 0);

  x = create_var("x");
  y = c_frac("1", "2");
  EXPECT_STREQ(print_string(add(x, y)).c_str(), "1//2+x");

  x = c_frac("1", "2");
  y = c_sin("y");
  EXPECT_STREQ(print_string(add(x, y)).c_str(), "1//2+sin(y)");
}

TEST(Sym, Nature)
{
  //
  // 常数与变量比较
  //
  symbol_t x = gConstE;
  symbol_t y = gConstPI;
  symbol_t z = add(x, y);
  EXPECT_STREQ(print_string(z).c_str(), "e+pi");

  x = gConstE;
  y = gConstInf;
  z = add(x, y);
  EXPECT_STREQ(print_string(z).c_str(), "inf");

  x = create_var("x");
  y = gConstE;
  z = add(x, y);
  EXPECT_STREQ(print_string(z).c_str(), "e+x");

  x = gConstPI;
  y = c_sin("y");
  EXPECT_STREQ(print_string(add(x, y)).c_str(), "pi+sin(y)");
}

TEST(Sym, VarFunc)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z = add(x, y);
  EXPECT_STREQ(print_string(z).c_str(), "x+y");

  x = create_sym("x");
  y = create_sym("x");
  z = add(x, y);
  EXPECT_STREQ(print_string(z).c_str(), "2*x");

  x = create_sym("x");
  y = c_cos("a");
  z = add(x, y);
  EXPECT_STREQ(print_string(z).c_str(), "x+cos(a)");

  x = c_cos("a");
  y = c_cos("a");
  z = add(x, y);
  EXPECT_STREQ(print_string(z).c_str(), "2*cos(a)");
}

TEST(Sym, Basic)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z1 = c_add(x, y);
  symbol_t z2 = c_mul(x, y);
  symbol_t a = create_sym("a");
  symbol_t r = add(a, z1);
  EXPECT_STREQ(print_string(r).c_str(), "a+x+y");
  r = add(a, z2);
  EXPECT_STREQ(print_string(r).c_str(), "a+x*y");
  x = create_sym("x");
  y = create_sym("a");
  z1 = add(x, y);
  r = add(a, z1);
  EXPECT_STREQ(print_string(r).c_str(), "x+2*a");
}

TEST(Sym, Basic2)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z1 = c_mul(x, y);
  symbol_t z2 = c_mul(x, y);
  symbol_t z3 = add(z1, z2);
  EXPECT_STREQ(print_string(z3).c_str(), "2*x*y");
  x = create_sym("a");
  y = create_sym("b");
  z2 = c_mul(x, y);
  z3 = add(z1, z2);
  EXPECT_STREQ(print_string(z3).c_str(), "a*b+x*y");

  symbol_t a = create_sym("x");
  symbol_t b = create_sym("a");
  z1 = add(x, y);
  // std::cout << print_string(z1) << std::endl;
  z2 = add(a, b);
  // std::cout << print_string(z2) << std::endl;
  z3 = add(z1, z2); // (x+y) + (x+a) = a+y+2*x
  EXPECT_STREQ(print_string(z3).c_str(), "b+x+2*a");

  z2 = c_mul(x, y);
  z3 = add(z1, z2);
  EXPECT_STREQ(print_string(z3).c_str(), "a+b+a*b");
}

TEST(Sym, Unit)
{
  //
  // 常数与变量比较
  //
  symbol_t x = create_symbol("x");
  symbol_t y = x + gConstZero;
  // std::cout << y << std::endl;
  EXPECT_TRUE(y == x);
}

TEST(Sym, Log)
{
  //
  // 常数与变量比较
  //
  symbol_t b = create_symbol("x");
  symbol_t e1 = create_symbol("5");
  symbol_t e2 = c_frac("1", "2");
  symbol_t y1 = c_log(b, e1);
  symbol_t y2 = c_log(b, e2);
  // std::cout << y1 + y2 << std::endl;
  EXPECT_STREQ(print_string(y1+y2).c_str(), "log(x,5//2)");
  e1 = create_symbol("a");
  y1 = c_log(b, e1);
  EXPECT_STREQ(print_string(y1+y2).c_str(), "log(x,1//2*a)");
}

TEST(Sym, Polynomial)
{
  //
  // 常数与变量比较
  //
  symbol_t x = create_symbol("x");
  symbol_t y = create_symbol("y");
  symbol_t z = create_symbol("z");
  symbol_t p1 = x + y;
  symbol_t p2 = x + "2"*y + z;
  symbol_t p3 = p1 + p2;
  EXPECT_STREQ(print_string(p3).c_str(), "z+2*x+3*y");

  symbol_t _z = opposite(z);
  symbol_t p4 = p3 + _z;
  EXPECT_STREQ(print_string(p4).c_str(), "2*x+3*y");
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}