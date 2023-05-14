#include <mysym/mysym.h>
#include "__misc.h"

#include <random>

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

  std::string random_string(size_t length)
  {
    char tmp;
    std::string buffer;
    std::random_device rd;
    std::default_random_engine random(rd());
    
    for (size_t i = 0; i < length; i++) {
      tmp = random() % 36;
      if (tmp < 10) {
        tmp += '0';
      } else {
        tmp -= 10;
        tmp += 'A';
      }
      buffer += tmp;
    }
    return buffer;
  }
} // namespace mysym