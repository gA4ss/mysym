#include <mysym/mysym.h>
#include <regex>

namespace mysym
{
  std::vector<std::string> split_string(std::string str, std::string regex_str/* = "[, ]+"*/)
  {
    std::vector<std::string> res;
    std::regex reg(regex_str);
    std::sregex_token_iterator pos(str.begin(), str.end(), reg, -1);
    decltype(pos) end; // 自动推导类型
    for (; pos != end; ++pos)
    {
      res.push_back(pos->str());
    }
    return res;
  }
} // namespace mysym