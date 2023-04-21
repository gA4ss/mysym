#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../src/set.h"

int main(int argc, char* argv[]) {
  mysym::set_t a = mysym::create_set({"11","22","33","44"});
  mysym::set_t b = mysym::create_set({"11","22","55"});
  mysym::set_t c = mysym::create_set({"11","22","55"});
  
  mysym::set_t d = mysym::intersection_set(a, b);
  std::cout << "d = " <<  mysym::print_string(d) << std::endl;
  mysym::set_t e = mysym::union_set(a, b);
  std::cout << "e = " <<  mysym::print_string(e) << std::endl;

  std::cout << "b,c : " << mysym::relation_set(b, c) << std::endl;
  std::cout << "a,b : " << mysym::relation_set(a, b) << std::endl;
  std::cout << "a,d : " << mysym::relation_set(a, d) << std::endl;
  std::cout << "d,a : " << mysym::relation_set(d, a) << std::endl;

  mysym::set_t x = mysym::import_set(a, b);
  std::cout << "x = " <<  mysym::print_string(x) << std::endl;
  return 0;
}