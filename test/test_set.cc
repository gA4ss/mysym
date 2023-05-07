#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../src/set.hpp"

std::string print_string(const mysym::set_t<int>& s)
{
  std::string str;
  for (auto it = s.elements.begin(); it != s.elements.end(); it++)
  {
    str += (it->first + ',');
  }
  str.pop_back();
  return str;
}

int main(int argc, char* argv[]) {
  mysym::set_t<int> a = mysym::create_set<int>({"11","22","33","44"}, {1,2,3,4});
  mysym::set_t<int> b = mysym::create_set<int>({"11","22","55"},{1,2,5});
  mysym::set_t<int> c = mysym::create_set<int>({"11","22","55"},{1,2,5});
  
  mysym::set_t<int> d = mysym::intersection_set<int>(a, b);
  std::cout << "d = " << print_string(d) << std::endl;
  mysym::set_t<int> e = mysym::union_set<int>(a, b);
  std::cout << "e = " << print_string(e) << std::endl;

  std::cout << "b,c : " << mysym::relation_set<int>(b, c) << std::endl;
  std::cout << "a,b : " << mysym::relation_set<int>(a, b) << std::endl;
  std::cout << "a,d : " << mysym::relation_set<int>(a, d) << std::endl;
  std::cout << "d,a : " << mysym::relation_set<int>(d, a) << std::endl;

  mysym::set_t<int> x = mysym::import_set<int>(a, b);
  std::cout << "x = " << print_string(x) << std::endl;
  return 0;
}