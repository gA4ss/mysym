#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/construct.h>

using namespace mysym;

TEST(Sym, Polynomial)
{
  symbol_t s1 = c_add("x", create_int("3")); // x + y
  EXPECT_TRUE(is_polynomial(s1, create_var("x")));
  symbol_t s2 = c_add(create_var("z"), c_mul(create_int("5"), "z")); // z + ab
  EXPECT_TRUE(is_polynomial(s2, create_var("z")));
  symbol_t s3 = c_mul(create_int("5"), "b");
  EXPECT_TRUE(is_polynomial(s3, create_var("b")));
  symbol_t s4 = c_pow(c_mul("a", "b"), create_int("5"));
  EXPECT_FALSE(is_polynomial(s4, create_var("b")));
  symbol_t s5 = c_pow("a", create_int("5"));
  symbol_t s6 = c_pow("a", create_int("3"));
  symbol_t s7 = c_add(s5, s6);
  EXPECT_TRUE(is_polynomial(s7, create_var("a")));
}

// std::vector<int> polynomial_t;
// int gcd(polynomial_t l)
// {
//   return 1;
// }

// int deg(const poly_t& p)
// {
//   if (p.size() == 0)
//   {
//     // 异常
//     return -1;
//   }
//   return p.size() - 1;
// }

// int lc(const poly_t &p)
// {
//   return p[deg(p)];
// }

// poly_t poly_mul(const poly_t& p, int c)
// {
//   poly_t q;
//   for (int i = 0; i < p.size(); i++)
//   {
//     q.push_back(c * p[i]);
//   }
//   return q;
// }

// bool poly_div_poly(const poly_t &f, const poly_t &g,
//                    poly_t &q, poly_t &r, int &delta)
// {
//   if (deg(f) < deg(g))
//   {
//     return false;
//   }

//   poly_t r = f;
//   int n = deg(g), k = deg(r);
//   poly_t s = 
  
//   while (k >= n)
//   {
//     q = 
//   }

//   return true;
// }

TEST(Sym, PolynomialDiv)
{
  std::cout << sizeof(int_t) << std::endl;
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}