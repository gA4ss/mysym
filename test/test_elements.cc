#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/wrapper.h>
#include <mysym/construct.h>

using namespace mysym;

TEST(Sym, Variables)
{
  symbol_t x = create_var("x");
  symbol_t y = create_var("y");
  symbol_t z = create_var("z");
  symbol_t px3 = c_pow("x", create_int("3"));
  symbol_t py2 = c_pow("y", create_int("2"));
  symbol_t xay = c_add(px3, py2);
  symbol_t epr = x + y + z + x * y * z + px3 * py2 + px3 + py2 + xay;
  std::cout << print_string(epr) << std::endl;
  list_t l = variables(epr);
  std::cout << print_string(l) << std::endl;
  l = abstract_variables(epr);
  std::cout << print_string(l) << std::endl;
}

TEST(Sym, Constants)
{
  symbol_t x = create_var("x");
  symbol_t y = create_var("y");
  symbol_t z = create_var("z");
  symbol_t px3 = x ^ create_int("3");
  symbol_t py2 = y ^ create_int("4");
  symbol_t logyn5 = log(y, create_int("5"));
  symbol_t xay = c_add(px3, py2);
  symbol_t epr = x + y + z + x * y * z + px3 * py2 + px3 + py2 + xay + logyn5;
  std::cout << print_string(epr) << std::endl;
  list_t l = constants(epr);
  std::cout << print_string(l) << std::endl;
}

TEST(Sym, Integers)
{
  symbol_t x = create_var("x");
  symbol_t y = create_var("y");
  symbol_t z = create_var("z");
  symbol_t px3 = x ^ create_int("3");
  symbol_t py2 = y ^ create_int("4");
  symbol_t logyn5 = log(y, create_int("5"));
  symbol_t xay = px3 + py2;
  symbol_t fr = frac(px3, z ^ create_int("7"));
  symbol_t epr = x + y + z + x * y * z + px3 * py2 + px3 + py2 + xay + logyn5 * fr;
  std::cout << print_string(epr) << std::endl;
  list_t l = integers(epr);
  std::cout << print_string(l) << std::endl;
}

TEST(Sym, Reals)
{
  symbol_t x = create_var("x");
  symbol_t y = create_var("y");
  symbol_t z = create_var("z");
  symbol_t px3 = x ^ create_int("3");
  symbol_t py2 = y ^ create_int("4");
  symbol_t logyn5 = log(y, create_int("5"));
  symbol_t xay = px3 + py2;
  symbol_t fr = frac(px3, z ^ create_int("7.5"));
  symbol_t epr = x + y + z + x * y * z + px3 * py2 + \
                 px3 + py2 + xay + logyn5 * fr + create_flt("1.5");
  std::cout << print_string(epr) << std::endl;
  list_t l = reals(epr);
  std::cout << print_string(l) << std::endl;
}

TEST(Sym, Logs)
{
  symbol_t x = create_var("x");
  symbol_t y = create_var("y");
  symbol_t z = create_var("z");
  symbol_t px3 = x ^ create_int("3");
  symbol_t py2 = y ^ create_int("4");
  symbol_t logyn5 = log(y, create_int("5"));
  symbol_t xay = px3 + py2;
  symbol_t fr = frac(px3, z ^ create_int("7.5"));
  symbol_t epr = x + y + z + x * y * z + px3 * py2 + \
                 px3 + py2 + xay + logyn5 * fr + create_flt("1.5");
  std::cout << print_string(epr) << std::endl;
  list_t l = logs(epr);
  std::cout << print_string(l) << std::endl;
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}