#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Sort)
{
  std::string x = "zAx114314321ABC";
  std::string y = "y431432";
  if (x > y) std::cout << "x > y" << std::endl;
  else std::cout << "x < y" << std::endl;
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}