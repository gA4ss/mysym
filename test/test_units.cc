#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

// TEST(Sym, Variables)
// {
//   symbol_t x = create_sym("x");
//   symbol_t y = create_sym("y");
//   symbol_t z = c_add(x, y);
//   z = c_mul(create_int("5"), z);
//   list_t l = variables(z);
//   std::cout << print_string(l) << std::endl;
// }

// TEST(Sym, Variables)
// {
//   symbol_t x = create_sym("x");
//   symbol_t y = create_sym("y");
//   symbol_t z = c_add(x, y);
//   z = c_mul(create_int("5"), z);
//   list_t l = variables(z);
//   std::cout << print_string(l) << std::endl;
// }

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}