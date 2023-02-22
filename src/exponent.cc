#include <mysym/mysym.h>

namespace mysym
{
  symbol_t base(const symbol_t &s)
  {
    if (is_none(kind(s)))
    {
      return undefined;
    }
    return operand(s, 0);
  }

  symbol_t exponent(const symbol_t &s)
  {
    if (is_none(kind(s)))
    {
      return undefined;
    }
    else if (kind(s) == kOptPow)
    {
      return operand(s, 1);
    }
    return create_int("1");
  }
} // namespace mysym