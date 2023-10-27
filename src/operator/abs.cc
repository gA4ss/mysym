#include <mysym/mysym.h>

namespace mysym
{
  symbol_t abs(const symbol_t &x)
  {
    if (sign(x) == kSignNegative)
    {
      symbol_t _x = mul(gConstNegOne, x);
      return _x;
    }
    return default_func_handler(kOptAbs, x);
  }
} // namespace mysym