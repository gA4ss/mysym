#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Create)
{
  symbol_t s1 = create_var("x");
  symbol_t s2 = create_sym("y");
  symbol_t s3 = create_var("z");
  symbol_t s4 = create_sym("a");
  symbol_t s5 = create_sym("2");

  symbol_t r = c_mul(c_add(s1, s2), c_pow(s5, s4));
  std::string s = print_string(r);
  std::cout << s << std::endl;

  r = c_minus("t");
  std::cout << print_string(r) << std::endl;

  s1 = c_log("2", "x");
  r = c_minus(s1);
  std::cout << print_string(r) << std::endl;
}

TEST(Sym, Create2)
{
  symbol_t s1 = c_add("x", "y");
  symbol_t s2 = c_add(create_var("z"), c_mul("a", "b"));
  symbol_t s3 = c_add(s1, create_var("i"));
  symbol_t r = c_add(s3, s2);
  std::cout << print_string(r) << std::endl;
  // merge_same_operator(r);
  // std::cout << print_string(r) << std::endl;

  r = c_add(c_pow("2", "x"),
            c_sub(c_sub(c_add("x", "y"), c_add(c_add("z", "t"), c_add("k", "i"))),
                  c_add("a", "b")));
  std::cout << print_string(r) << std::endl;
  // merge_same_operator(r);
  // std::cout << print_string(r) << std::endl;

  r = c_add(c_add(c_mul(c_mul(c_add("u", "v"), create_var("w")), create_var("x")), create_var("y")),
            create_var("z"));
  std::cout << print_string(r) << std::endl;
  // merge_same_operator(r);
  // std::cout << print_string(r) << std::endl;
}

// TEST(Sym, Opt) {
//   symbol_ptr_t s1 = add_("x", "y");
//   symbol_ptr_t s2 = add(create_var("z"), mul_("a", "b"));
//   symbol_ptr_t s3 = add(s1, create_var("i"));
// }

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}