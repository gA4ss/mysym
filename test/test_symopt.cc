#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, SymOpt)
{
  std::cout << symopts() << std::endl;
}

TEST(Sym, OptSet)
{
  std::cout << optsets() << std::endl;
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}