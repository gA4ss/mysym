#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/construct.h>

using namespace mysym;

TEST(Sym, Rule)
{
  // std::string ops;
  // append_optcase_string(ops, "basic,atom,const,func");
  // append_optcase_string(ops, kOptPow);
  // append_optcase_string(ops, kOptLog);
  rule_table_t tab = rule_library().cases[kOptAdd];
  for (auto it = tab.begin(); it != tab.end(); it++)
  {
    std::cout << it->first << std::endl;
  }
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}