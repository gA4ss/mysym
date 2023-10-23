#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Sign)
{
  symbol_t x = create_var("x");
  symbol_t y = create_var("y");
  symbol_t x3 = c_pow("x", create_int("3"));
  symbol_t y3 = c_pow("y", create_int("2"));
  symbol_t xpy = c_add(x3, y3);
  EXPECT_TRUE(sign(xpy));
  symbol_t e = gConstE;
  symbol_t ninf = gConstNegInf;
  EXPECT_TRUE(sign(e));
  EXPECT_TRUE(!sign(ninf));
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}