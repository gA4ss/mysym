/* 匹配两个符号，在送入match函数中时，必须保证每个符号表达式都是经过排序的。
 */
#include <mysym/mysym.h>

namespace mysym
{
  bool match(const symbol_t &s1, const symbol_t &s2)
  {
    return cmp(s1, s2) == 0 ? true : false;
  }

  bool match_in(const symbol_t &s1, const symbol_t &s2)
  {
    if (cmp(s1, s2) == 0)
      return true;
  
    // s1 != s2

    if (is_single(s2))
      return false;

    for (auto it = s2.items.begin(); it != s2.items.end(); it++)
    {
      if (match_in(s1, *it))
        return true;
    }

    return false;
  }
} // namespace mysym