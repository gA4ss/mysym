/* 匹配两个符号，在送入match函数中时，必须保证每个符号表达式都是经过排序的。
 */
#include <mysym/mysym.h>

namespace mysym
{
  bool match(const symbol_t &s1, const symbol_t &s2)
  {
    if ((is_var(kind(s1))) && (is_var(kind(s2))))
      return (s1.literal == s2.literal);
    return false;
  }

  bool match_in(const symbol_t &s1, const symbol_t &s2)
  {
    return false;
  }

  bool abstract_match(const symbol_t &s1, const symbol_t &s2)
  {
    return false;
  }

  bool abstract_match_in(const symbol_t &s1, const symbol_t &s2)
  {
    return false;
  }

} // namespace mysym