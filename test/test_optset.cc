#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <mysym/mysym.h>
#include <mysym/construct.h>

using namespace mysym;

TEST(Sym, OptSetCreate)
{
  optset_t os = create_optset_exclude("tmp", "basic, order, basicf, ^, !, none");
  std::string str = print_string(os);
  std::cout << str << std::endl;
}

void print_optset_priority(optset_t &os)
{
  std::cout << "priority array : " << std::endl;
  for (auto p : os.priority_array)
  {
    std::cout << p << " ";
  }
  std::cout << std::endl;
  std::cout << "min priority : " << os.min_priority << std::endl;
  std::cout << "max priority : " << os.max_priority <<  std::endl;
  std::cout << "average priority : " << os.average_priority <<  std::endl;
}

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
  print_optset_priority(const_set);
  print_optset_priority(atom_set);
}

int main(int argc, char *argv[])
{
  init();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}