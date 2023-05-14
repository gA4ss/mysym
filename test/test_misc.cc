#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <memory>
#include <vector>
#include <regex>
#include <iostream>
#include <stdexcept>

#include "../src/__misc.h"

// template<typename ... Args>
// std::string string_format( const std::string& format, Args ... args )
// {
//   int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
//   if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
//   auto size = static_cast<size_t>( size_s );
//   std::unique_ptr<char[]> buf( new char[ size ] );
//   std::snprintf( buf.get(), size, format.c_str(), args ... );
//   return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
// }

int main(int argc, char* argv[]) {
  std::string s1 = "hello", s2 = "world";
  std::cout << s1 + " " + s2 << std::endl;

  std::cout << mysym::random_string() << std::endl;
  return 0;
}