#include <mysym/mysym.h>

namespace mysym
{
  symbol_t base(const symbol_t &s)
  {
    if (is_none(kind(s)) || (is_basic(kind(s))))
    {
      return undefined;
    }
    else if (is_atom(kind(s)))
    {
      return s;
    }
    if (size(s))
      return operand(s, 0);
    return gConstUDF;
  }
} // namespace mysym