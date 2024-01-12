#include <mysym/mysym.h>

namespace mysym
{
  symbol_t term(const symbol_t &s)
  {
    if (is_sym(kind(s)) || (is_add(kind(s))))
      return s;

    if (is_const(kind(s)))
      return gConstOne;

    //
    // 到这里只剩乘法操作
    // 排序与自动化简保证了，第一个参数是常数。
    //
    if (is_const(kind(operand(s, 0))))
    {
      symbol_t u = s;
      u.items.erase(u.items.begin());

      // 仅有一个元素，则直接变成单个符号。
      if (size(u) == 1)
      {
        u = u[0];
      }
      return u;
    }

    return s;
  }
} // namespace mysym