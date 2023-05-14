#ifndef MYSYM_MISC_H_
#define MYSYM_MISC_H_

#include <string>
#include <vector>
#include <regex>

namespace mysym
{
  std::vector<std::string> split_string(std::string str, std::string regex_str = "[, ]+");
  std::string random_string(size_t length = 16);
} // namespace mysym

#endif // MYSYM_MISC_H_