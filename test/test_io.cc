#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/wrapper.h>

using namespace mysym;

TEST(Sym, Opt)
{
  symopt_t opt;
  find_symopt("+", opt);
  std::cout << "opt = " <<print_string(opt) << std::endl;
}

TEST(Sym, Out)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z = create_sym("z");
  symbol_t _x = c_mul("-1", "x");
  std::cout << _x << std::endl;

  _x = mul(gConstNegOne, _x);
  std::cout << _x << std::endl;

  symbol_t _y = c_mul("-1", c_mul("-1", c_mul(y, z)));
  std::cout << _y << std::endl;
  std::cout << abs(_y) << std::endl;

  symbol_t n = create_int("-5");
  std::cout << "n = " << n << " " 
            << "abs(n) = " << abs(n) << std::endl;
}

TEST(Sym, In)
{
  symbol_t x,y;
  std::cin >> x;
  std::cin >> y;
  symbol_t z = x+y;
  std::cout << z << std::endl;

  z = c_add(x, gConstZero);
  std::cout << z << std::endl;
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}