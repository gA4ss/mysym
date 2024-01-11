#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/wrapper.h>

using namespace mysym;

TEST(Sym, Case1)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z = create_sym("z");

  symbol_t ans = div(x, y);
  EXPECT_STREQ(print_string(ans).c_str(), "x*y^-1");

  ans = div(x, x);
  EXPECT_STREQ(print_string(ans).c_str(), "1");

  ans = div(x, gConstInf);
  EXPECT_STREQ(print_string(ans).c_str(), "0");

  // ans = div(x, opposite(x));
  // EXPECT_STREQ(print_string(ans).c_str(), "-1");

  symbol_t poly = (x^create_int("2")) + (y^create_int("-1"));
  EXPECT_STREQ(print_string(poly).c_str(), "x^2+y^-1");

  ans = div(gConstOne, gConstE);
  EXPECT_STREQ(print_string(ans).c_str(), "e^-1");
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}