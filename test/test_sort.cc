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
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}