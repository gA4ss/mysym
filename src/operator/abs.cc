#include <mysym/mysym.h>

namespace mysym
{
  symbol_t abs(const symbol_t &x)
  {
    // 只有确切到具体数值才能直接进行绝对值运算
    if (symbol_is_number(x))
    {
      if (sign(x) == kSignNegative)
      {
        symbol_t _x = mul(gConstNegOne, x);
        return _x;
      }
    }
    return default_func_handler(kOptAbs, x);
  }
} // namespace mysym