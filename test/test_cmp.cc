#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Cmp)
{
  //
  // 常数与变量比较
  //
  symbol_t x = create_var("x");
  symbol_t c1 = create_real("1.5");
  EXPECT_EQ(cmp(x, c1), 1);

  symbol_t fr = c_frac(c1, create_int("5"));
  EXPECT_EQ(cmp(x, fr), 1);

  //
  // 常数与常数间比较
  //
  symbol_t c2 = create_real("3.14");
  symbol_t c3 = create_real("2.78");
  EXPECT_EQ(cmp(c3, c2), -1);
  EXPECT_EQ(cmp(c2, c3), 1);
  EXPECT_EQ(cmp(c2, c2), 0);

  EXPECT_EQ(cmp(c1, fr), 1);
  EXPECT_EQ(cmp(fr, c2), -1);
  EXPECT_EQ(cmp(c3, fr), 1);

  //
  // 符号间的比较
  //
  symbol_t y = create_var("y");
  EXPECT_EQ(cmp(x, y), -1);
  EXPECT_EQ(cmp(x, x), 0);

  //
  // 符号与函数间比较
  //
  symbol_t sinx = c_sin("x");
  EXPECT_EQ(cmp(sinx, x), 1);
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}