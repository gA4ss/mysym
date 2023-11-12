#include <mysym/mysym.h>

namespace mysym
{
  symbol_t abs(const symbol_t &x)
  {
    // 对负无穷的处理
    if (is_neg_inf(kind(x)))
      return gConstInf;

    if (sign(x) == kSignNegative)
    {
      symbol_t _x = mul(gConstNegOne, x);
      return _x;
    }
    return default_func_handler(kOptAbs, x);
  }
} // namespace mysym