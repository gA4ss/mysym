#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/wrapper.h>
#include <mysym/construct.h>

using namespace mysym;

TEST(Sym, Coefficient)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z = create_sym("z");
  symbol_t _x = c_mul("-1", "x");
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}