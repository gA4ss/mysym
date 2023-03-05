#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Expression) {
  symbol_t s1 = c_add("x", create_int("1"));
  symbol_t s2 = c_mul(create_var("a"), s1);
  symbol_t s3 = c_mul(create_int("3"), c_cos("y"));
  symbol_t s4 = c_add(s2, s3);
  std::cout << print_string(s4) << std::endl;

  list_t l = complete_sub_expressions(s4);
  std::cout << print_string(l) << std::endl;
}

TEST(Sym, Free) {
  symbol_t s1 = c_add("x", create_int("1"));
  symbol_t s2 = c_mul(create_var("a"), s1);
  symbol_t s3 = c_mul(create_int("3"), c_cos("y"));
  symbol_t s4 = c_add(s2, s3);
  std::cout << print_string(s4) << std::endl;

  EXPECT_TRUE(free_of(s4, create_var("u")));
  EXPECT_FALSE(free_of(s4, s3));
  EXPECT_FALSE(free_of(s4, s2));
  EXPECT_FALSE(free_of(s4, s1));
  EXPECT_FALSE(free_of(s4, s4));
}

int main(int argc, char* argv[]) {
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}