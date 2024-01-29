#include <mysym/mysym.h>

namespace mysym
{
  symbol_t term(const symbol_t &s)
  {
    if (is_mul(kind(s)))
    {
      if (is_const(kind(operand(s, 0))))
      {
        symbol_t u = s;
        u.items.erase(u.items.begin());

        // 仅有一个元素，则直接变成单个符号。
        if (size(u) == 1)
        {
          return u[0];
        }
        return u;
      }
    }

    if (is_const(kind(s)))
      return gConstOne;
    return s;
  }

  list_t terms(const symbol_t &s)
  {
    list_t l;
    if (is_mul(kind(s)))
    {
      for (auto a : s.items)
      {
        if (is_const(kind(a)))
          continue;
        else
          append(l, a);
      }
    }
    return l;
  }
} // namespace mysym