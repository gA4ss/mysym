#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/construct.h>
#include <mysym/wrapper.h>

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
  
  symbol_t x = create_sym("x");
  symbol_t y = create_sym("y");
  symbol_t z = create_sym("z");
  symbol_t k = create_sym("k");
  symbol_t i = create_sym("i");
  symbol_t t = create_sym("t");
  symbol_t a = create_sym("a");
  symbol_t b = create_sym("b");

  symbol_t p = (x+y) - (z+t);
  std::cout << p << std::endl;

  symbol_t o1 = create_int("2") ^ x;
  symbol_t o2 = ((x+y) - ((z+t) + (k+i))) - (a+b);
  symbol_t o3 = o1 + o2;
  std::cout << o3 << std::endl;

  // r = c_add(c_pow("2", "x"),
  //           c_sub(c_sub(c_add("x", "y"), c_add(c_add("z", "t"), c_add("k", "i"))),
  //                 c_add("a", "b")));
  // std::cout << print_string(r) << std::endl;


  // merge_same_operator(r);
  // std::cout << print_string(r) << std::endl;
}

TEST(Sym, Bug)
{
  symbol_t u = create_sym("u");
  symbol_t v = create_sym("v");
  symbol_t w = create_sym("w");
  symbol_t p1 = mul(mul(u, v), w);

  // symbol_t r = c_add(c_add(c_mul(c_mul(c_add("u", "v"), create_var("w")), create_var("x")), create_var("y")),
  //                    create_var("z"));
  EXPECT_STREQ(print_string(p1).c_str(), "u*v*w");
}

TEST(Sym, Create3)
{
  symbol_t s1 = create_var("x");
  symbol_t s2 = create_sym("y");
  symbol_t s3 = create_var("a");
  symbol_t s4 = create_sym("b");

  symbol_t r = make(kOptSub, s1, s2);
  EXPECT_STREQ(print_string(r).c_str(), "x+-1*y");

  // r = pow(create_int("-1"), s4);
  // std::cout << r << std::endl;

  symbol_t a = create_int("-1") * s3;
  EXPECT_STREQ(print_string(a).c_str(), "-1*a");
  a = opposite(a);
  EXPECT_STREQ(print_string(a).c_str(), "a");

  r = make(kOptDiv, s3, s4);
  EXPECT_STREQ(print_string(r).c_str(), "a*b^-1");

  r = c_minus("t");
  EXPECT_STREQ(print_string(r).c_str(), "-1*t");
}

TEST(Sym, CreateList)
{
  symbol_items_t l = {create_sym("x"),create_sym("y"), create_sym("z")};
  symbol_t m = create_monomial(l);
  std::cout << print_string(m) << std::endl;

  l = {create_sym("x"),create_sym("y"), create_sym("z")};
  m = create_polynomial(l);
  std::cout << print_string(m) << std::endl;
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}