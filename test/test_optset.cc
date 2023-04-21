#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Set)
{
  list_t l;
  symbol_t x = create_var("x");
  append(l, x);
  symbol_t y = create_var("y");
  append(l, y);
  symbol_t z = create_var("z");
  append(l, z, true);
  append(l, z, true);
  append(l, z, true);
  EXPECT_EQ(size(l), 3);

  std::cout << print_string(l) << std::endl;
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}