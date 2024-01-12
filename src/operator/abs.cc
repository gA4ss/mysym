#include <mysym/mysym.h>

namespace mysym
{
  symbol_t abs(const symbol_t &x)
  {
    // 对一些特殊值的处理
    if (is_neg_inf(kind(x)))
      return gConstInf;
    else if (compare(x, gConstZero) == 0)
      return x;

    if (sign(x) == kSignNegative)
    {
      return opposite(x);
    }
    return default_func_handler(kOptAbs, x);
  }
} // namespace mysym