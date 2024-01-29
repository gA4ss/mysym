#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/wrapper.h>
#include <mysym/construct.h>

using namespace mysym;

// TEST(Sym, PrintSub)
// {
//   rule_library_t lib = rule_library();
//   for (auto it = lib.cases[kOptSub].begin(); it != lib.cases[kOptSub].end(); it++)
//   {
//     std::cout << it->first << std::endl;
//   }
// }

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
  EXPECT_STREQ(print_string(z).c_str(), "0");
  z = sub(x, y);
  EXPECT_STREQ(print_string(z).c_str(), "0");
}

TEST(Sym, SubSymMul)
{
  symbol_t x = create_symbol("x");
  symbol_t y = create_symbol("y");
  symbol_t x3 = mul(create_int("3"), x);
  symbol_t z = sub(x, x3);
  EXPECT_STREQ(print_string(z).c_str(), "-2*x");
}

TEST(Sym, SubSymAdd)
{
  symbol_t x = create_symbol("x");
  symbol_t y = create_symbol("y");
  symbol_t xy = add(x, y);
  symbol_t z = sub(xy, x);
  EXPECT_STREQ(print_string(z).c_str(), "y");
}

TEST(Sym, SubMulAdd)
{
  symbol_t x = create_symbol("x");
  symbol_t y = create_symbol("y");
  symbol_t xy = mul(x, y);
  symbol_t _2xy = "-2" * xy;
  symbol_t poly = x + y + xy;
  symbol_t p = poly - _2xy;
  EXPECT_STREQ(print_string(p).c_str(), "x+y+3*x*y");
  p = xy + _2xy + x;
  EXPECT_STREQ(print_string(p).c_str(), "x+-1*x*y");
}

TEST(Sym, SubAddAdd)
{
  symbol_t x = create_symbol("x");
  symbol_t _x = opposite(x);
  symbol_t y = create_symbol("y");
  symbol_t z = create_symbol("z");
  symbol_t t = create_sym("t");
  
  symbol_t p = (x+y) - (z+t);
  // std::cout << p << std::endl;
  EXPECT_STREQ(print_string(p).c_str(), "x+y+-1*t+-1*z");

  p = ("2"*y);
  p = _x - p;
  p = p + z;
  EXPECT_STREQ(print_string(p).c_str(), "z+-2*y+-1*x");
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}