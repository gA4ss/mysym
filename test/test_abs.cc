#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/construct.h>

using namespace mysym;

TEST(Sym, Abs)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z = create_sym("z");

  symbol_t _x = c_mul("-1", "x");
  std::cout << print_string(_x) << std::endl;
  std::cout << print_string(abs(_x)) << std::endl;

  _x = mul(gConstOne, _x);
  std::cout << print_string(_x) << std::endl;

  symbol_t _y = c_mul("-1", c_mul("-1", c_mul(y, z)));
  std::cout << print_string(_y) << std::endl;
  std::cout << print_string(abs(_y)) << std::endl;

  symbol_t n = create_int("-5");
  std::cout << "n = " << print_string(n) << " " 
            << "abs(n) = " << print_string(abs(n)) << std::endl;
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}