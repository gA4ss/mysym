#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/wrapper.h>

using namespace mysym;

TEST(Sym, Wrapper)
{
  symbol_t e1 = create(kOptAdd);
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t a = create_sym("a");
  symbol_t b = create_sym("b");
  append(e1, {y,a,b});
  for (size_t i = 0; i < size(e1); i++)
    std::cout << print_string(e1[i]);
  std::cout << std::endl;

  symbol_t z = a / b;
  std::cout << print_string(z) << std::endl;

  symbol_t u = x + y;
  std::cout << print_string(u) << std::endl;
  std::cout << print_string(u * u) << std::endl;
  symbol_t k = a + b;
  std::cout << print_string(k) << std::endl;
  std::cout << print_string(u * k) << std::endl;
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}