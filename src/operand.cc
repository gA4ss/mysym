#include <mysym/mysym.h>

namespace mysym
{
  /* 当s是符号（变量、整数、小数）并且i是0索引，直接返回本身。
   */
  symbol_t operand(const symbol_t &s, size_t i)
  {
    if (is_atom(kind(s)))
    {
      if (i == 0)
      {
        return s;
      }
      else
      {
        mysym_param_is_out_of_range_exception("i = %lu", i);
      }
    }

    if (i >= symbol_size(s))
    {
      mysym_param_is_out_of_range_exception("i = %lu", i);
    }
    return s.items[i];
  }
} // namespace mysym