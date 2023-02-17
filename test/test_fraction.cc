#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, Fraction) {
  symbol_t s1 = frac("x", "y");
  std::cout << print_string(s1) << std::endl;
  symbol_t s2 = add(create_sym("z"), mul("a", "b")); // z + ab
  symbol_t s3 = mul("a", "b");
  symbol_t s4 = frac(s2, s3);
  std::cout << print_string(s4) << std::endl;
  symbol_t s5 = pow("a", create_int("5"));
  symbol_t s6 = pow("b", create_int("3"));
  symbol_t s7 = frac(s5,s6);
  std::cout << print_string(s7) << std::endl;
}

TEST(Sym, FractionTools) {
  symbol_t s1 = frac("x", "y");
  std::cout << print_string(numerator(s1)) << std::endl;
  symbol_t s2 = add(create_sym("z"), mul("a", "b")); // z + ab
  symbol_t s3 = mul("a", "b");
  symbol_t s4 = frac(s2, s3);
  std::cout << print_string(denominator(s4)) << std::endl;
  symbol_t s5 = pow("a", create_int("5"));
  symbol_t s6 = pow("b", create_int("3"));
  symbol_t s7 = frac(s5,s6);
  std::cout << print_string(frac_to_product(s7)) << std::endl;
}

int main(int argc, char* argv[]) {
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}