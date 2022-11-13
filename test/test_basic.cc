#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Create) {
  symbol_ptr_t s1 = create_var("x");
  symbol_ptr_t s2 = create_var("y");
  symbol_ptr_t s3 = create_var("z");
  symbol_ptr_t s4 = create_var("a");
  symbol_ptr_t s5 = create_const("2");

  symbol_ptr_t r = mul(add(s1, s2), exp(s5, s4));
  std::string s = print_string(r);
  std::cout << s << std::endl;

  r = minus_("t");
  std::cout << print_string(r) << std::endl;

  s1 = log_("2", "x");
  r = minus(s1);
  std::cout << print_string(r) << std::endl;
}

TEST(Sym, Merge) {
  symbol_ptr_t s1 = add_("x", "y");
  symbol_ptr_t s2 = add(create_var("z"), mul_("a", "b"));
  symbol_ptr_t s3 = add(s1, create_var("i"));
  symbol_ptr_t r = add(s3, s2);
  std::cout << print_string(r) << std::endl;
  merge_same_operator(r);
  std::cout << print_string(r) << std::endl;

  r = add(exp_("2", "x"), 
          sub(sub(add_("x", "y"), add(add_("z", "t"), add_("k", "i"))), 
              add_("a", "b")));
  std::cout << print_string(r) << std::endl;
  merge_same_operator(r);
  std::cout << print_string(r) << std::endl;
}

int main(int argc, char* argv[]) {
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}