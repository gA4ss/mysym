#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Create) {
  symbol_t s1 = create_sym("x");
  symbol_t s2 = create_sym("y");
  symbol_t s3 = create_sym("z");
  symbol_t s4 = create_sym("a");
  symbol_t s5 = create_sym("2");

  symbol_t r = mul(add(s1, s2), pow(s5, s4));
  std::string s = print_string(r);
  std::cout << s << std::endl;

  r = minus("t");
  std::cout << print_string(r) << std::endl;

  s1 = log("2", "x");
  r = minus(s1);
  std::cout << print_string(r) << std::endl;
}

TEST(Sym, Create2) {
  symbol_t s1 = add("x", "y");
  symbol_t s2 = add(create_sym("z"), mul("a", "b"));
  symbol_t s3 = add(s1, create_sym("i"));
  symbol_t r = add(s3, s2);
  std::cout << print_string(r) << std::endl;
  // merge_same_operator(r);
  // std::cout << print_string(r) << std::endl;

  r = add(pow("2", "x"), 
          sub(sub(add("x", "y"), add(add("z", "t"), add("k", "i"))), 
              add("a", "b")));
  std::cout << print_string(r) << std::endl;
  // merge_same_operator(r);
  // std::cout << print_string(r) << std::endl;

  r = add(add(mul(mul(add("u", "v"), create_sym("w")), create_sym("x")), create_sym("y")), 
          create_sym("z"));
  std::cout << print_string(r) << std::endl;
  // merge_same_operator(r);
  // std::cout << print_string(r) << std::endl;
}

TEST(Sym, Opt) {
  for (int i = 0; i < kOptMax; i++)
  {
    std::cout << opt_name(i) << ", "
              << opt_prio(i) << ", "
              << opt_asso(i) << ", "
              << std::endl;
  }
  std::cout << std::endl;
}

TEST(Sym, List) {
  symbol_t s1 = add("x", "y");
  symbol_t s2 = add(create_sym("z"), mul("a", "b"));
  symbol_t s3 = add(s1, create_sym("i"));
  list_t l;
  insert(l, s1);
  insert(l, s2);
  insert(l, s3);
  insert(l, s3);
  std::cout << "cout = " << size(l) << "   " << print_string(l) << std::endl;
  clear(l);
  std::cout << "cout = " << size(l) << "   " << print_string(l) << std::endl;
}

// TEST(Sym, Opt) {
//   symbol_ptr_t s1 = add_("x", "y");
//   symbol_ptr_t s2 = add(create_sym("z"), mul_("a", "b"));
//   symbol_ptr_t s3 = add(s1, create_sym("i"));
// }

int main(int argc, char* argv[]) {
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}