#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>

using namespace mysym;

TEST(Sym, OptSet)
{
  // std::string os = optsets();
  // std::cout << os << std::endl;
  // optset_t s;
  // if (find_optset("all", s))
  //   std::cout << print_string(s) << std::endl;

  optset_t const_set, atom_set;
  EXPECT_TRUE(find_optset("const", const_set));
  EXPECT_TRUE(find_optset("atom", atom_set));
  opts_t iss = intersection_optset("const", "atom");
  EXPECT_EQ(iss.size(), size_optset("const"));
  EXPECT_EQ(relation_optset("const", "atom"), kSet2Include1);
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}