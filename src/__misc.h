#ifndef MYSYM_MISC_H_
#define MYSYM_MISC_H_

#include <string>
#include <vector>

namespace mysym
{
  std::vector<std::string> split_string(std::string str, std::string regex_str = "[, ]+");
} // namespace mysym

#endif // MYSYM_MISC_H_