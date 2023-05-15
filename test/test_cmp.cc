#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, PrintCmd)
{
  rule_library_t lib = rule_library();
  for (auto it = lib.cases[kOptCmp].begin(); it != lib.cases[kOptCmp].end(); it++)
  {
    std::cout << it->first << std::endl;
  }
}

TEST(Sym, Cmp3)
{
  //
  // 常数与变量比较
  //
  symbol_t x = create_var("x");
  symbol_t c1 = create_flt("1.5");
  EXPECT_EQ(compare(x, c1), 1);

  symbol_t fr = c_frac(c1, create_int("5"));
  EXPECT_EQ(compare(x, fr), 1);

  //
  // 常数与常数间比较
  //
  symbol_t c2 = create_flt("3.14");
  symbol_t c3 = create_flt("2.78");
  EXPECT_EQ(compare(c3, c2), -1);
  EXPECT_EQ(compare(c2, c3), 1);
  EXPECT_EQ(compare(c2, c2), 0);

  EXPECT_EQ(compare(c1, fr), 1);
  EXPECT_EQ(compare(fr, c2), -1);
  EXPECT_EQ(compare(c3, fr), 1);

  //
  // 符号间的比较
  //
  symbol_t y = create_var("y");
  EXPECT_EQ(compare(x, y), -1);
  EXPECT_EQ(compare(x, x), 0);

  //
  // 符号与函数间比较
  //
  symbol_t sinx = c_sin("x");
  EXPECT_EQ(compare(sinx, x), 1);
}

TEST(Sym, Cmp4)
{
  symbol_t p1 = c_pow("x", create_int("3"));
  EXPECT_EQ(compare(p1, p1), 0);

  symbol_t p2 = c_pow("y", create_int("2"));
  EXPECT_EQ(compare(p1, p2), -1);

  symbol_t p3 = c_pow("x", create_int("4"));
  EXPECT_EQ(compare(p3, p1), 1);

  symbol_t p4 = c_pow("x", c_frac("1", "4"));
  EXPECT_EQ(compare(p1, p4), 1);

  symbol_t x = c_mul("x", "y");
  symbol_t y = c_add("x", "y");
  symbol_t p5 = c_pow(y, x);
  symbol_t z = c_mul("x", "z");
  symbol_t p6 = c_mod(y, z);
  EXPECT_EQ(compare(p5, p6), -1);
  EXPECT_EQ(compare(p1, p5), -1);
}

TEST(Sym, Cmp5)
{
  symbol_t p1 = c_log("x", create_int("3"));
  EXPECT_EQ(compare(p1, p1), 0);

  symbol_t p2 = c_log("y", create_int("2"));
  EXPECT_EQ(compare(p1, p2), -1);

  symbol_t p3 = c_log("x", create_int("4"));
  EXPECT_EQ(compare(p3, p1), 1);

  symbol_t p4 = c_log("x", c_frac("1", "4"));
  EXPECT_EQ(compare(p1, p4), 1);
}

TEST(Sym, Cmp6)
{
  symbol_t p1 = c_mod("x", create_int("3"));
  EXPECT_EQ(compare(p1, p1), 0);

  symbol_t p2 = c_mod("y", create_int("2"));
  EXPECT_EQ(compare(p1, p2), -1);

  symbol_t p3 = c_mod("x", create_int("4"));
  EXPECT_EQ(compare(p3, p1), 1);

  symbol_t p4 = c_mod("x", create_int("2"));
  EXPECT_EQ(compare(p1, p4), 1);
}

TEST(Sym, Cmp7)
{
  symbol_t p1 = c_mod("x", create_int("3"));
  EXPECT_EQ(compare(p1, p1), 0);

  symbol_t p2 = c_mod("y", create_int("2"));
  EXPECT_EQ(compare(p1, p2), -1);

  symbol_t p3 = c_mod("x", create_int("4"));
  EXPECT_EQ(compare(p3, p1), 1);

  symbol_t p4 = c_mod("x", create_int("2"));
  EXPECT_EQ(compare(p1, p4), 1);
}

TEST(Sym, Cmp8)
{
  symbol_t a1 = c_add("x", "y");
  EXPECT_EQ(compare(a1, a1), 0);
  symbol_t p1 = c_mul("a", "b");
  EXPECT_EQ(compare(p1, p1), 0);
  EXPECT_EQ(compare(a1, p1), 1);
}

TEST(Sym, Cmp9)
{
  symbol_t a1 = c_add("x", "y");
  EXPECT_EQ(compare(a1, a1), 0);
  symbol_t a2 = c_add("a", "b");
  EXPECT_EQ(compare(a1, a2), 1);
  symbol_t p1 = c_mul("a", "b");
  EXPECT_EQ(compare(p1, p1), 0);
  symbol_t p2 = c_mul("x", "y");
  EXPECT_EQ(compare(p1, p2), -1);
}

TEST(Sym, Cmp10)
{
  symbol_t a1 = c_add("x", "y");
  symbol_t f1 = c_sin("a");
  EXPECT_EQ(compare(a1, f1), 1);
  symbol_t a2 = c_add("x", create_int("1"));
  symbol_t p1 = c_pow("a", create_int("5"));
  EXPECT_EQ(compare(a2, p1), 1);
}

TEST(Sym, Cmp11)
{
  symbol_t a1 = c_mul("x", "y");
  symbol_t f1 = c_sin("a");
  EXPECT_EQ(compare(a1, f1), -1);
  symbol_t a2 = c_mul("x", create_int("1"));
  symbol_t p1 = c_pow("a", create_int("5"));
  EXPECT_EQ(compare(a2, p1), -1);
}

// #endif

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}