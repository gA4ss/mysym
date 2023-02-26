#include <mysym/mysym.h>

namespace mysym
{
  symbol_t exponent(const symbol_t &s)
  {
    if (is_none(kind(s)))
    {
      return undefined;
    }
    else if ((kind(s) == kOptPow) || (kind(s) == kOptLog))
    {
      return operand(s, 1);
    }
    return create_int("1");
  }
} // namespace mysym