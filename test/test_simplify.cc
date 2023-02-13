#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, AutomaticSimplify) {
}

int main(int argc, char* argv[]) {
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}