#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Sort)
{
  symbol_t a = c_add("a", "y");
  symbol_t b = c_add("b", "c");
  symbol_t c = c_add(create_int("5"), "u");
  symbol_t d = c_add(c_pow("a", create_int("3")), c_sin("y"));
  symbol_t group1 = c_add(c_add(a, b), c_add(c, d));
  std::cout << "group1 = " << print_string(group1) << std::endl;
  sort(group1);
  std::cout << "after sort group1 = " << print_string(group1) << std::endl;
  sort(group1, true);
  std::cout << "after reverse group1 = " << print_string(group1) << std::endl;

  symbol_t x = create_var("x");
  a = c_pow("x", "2");
  b = c_mul(x, create_int("2"));
  c = create_int("1");
  symbol_t y1 = c_add(a, b);
  symbol_t y = c_add(y1, c);
  std::cout << "y = " << print_string(y) << std::endl;
  sort(y);
  std::cout << "after sort y = " << print_string(y) << std::endl;

  symbol_t pp = c_pow(create_var("x"), c_add(create_var("y"), create_var("1")));
  std::cout << "pp = " << print_string(pp) << std::endl;
  sort(pp);
  std::cout << "after sort pp = " << print_string(pp) << std::endl;
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}