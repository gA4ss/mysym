#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/wrapper.h>
#include <mysym/construct.h>

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

TEST(Sym, AppendErase)
{
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t a = create_sym("a");
  symbol_t b = create_sym("b");
  symbol_t e1 = x + y + a + b;
  symbol_t f = create_sym("f");
  symbol_t g = create_sym("g");
  symbol_t h = create_sym("h");
  symbol_t i = create_sym("i");
  symbol_t e2 = f + g + h + i;
  append(e1, e2, 2);
  std::cout << e1 << std::endl;
  e1 = x + y + a + b;
  append(e1, e2, 1, 3);
  std::cout << e1 << std::endl;

  erase(e1, 3);
  std::cout << e1 << std::endl;
  erase(e1, 4);
  std::cout << e1 << std::endl;
  erase(e1, 0);
  std::cout << e1 << std::endl;
  
  try
  {
    erase(e1, 5);
  }
  catch(const my::MyException& e)
  {
    std::cout << e.what() << std::endl;
    std::cout << e.type() << std::endl;
  }
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}