#include <mysym/mysym.h>

namespace mysym
{
  bool sign(const symbol_t &x)
  {
    //
    // 1. 如果是数字直接返回符号。
    // 2. 如果是常数直接返回不同的符号。
    // 3. 如果是分数，则返回分子的符号。
    // 4. 如果是变量直接返回正。
    // 5. 如果是函数直接返回正。
    // 6. 如果是乘号，则以第一个元素的符号为准。
    // 7. 如果是加号，则直接返回正。
    bool s = kSignPositive;
    if (is_num(kind(x)))
    {
      s = (compare(x, gConstZero) == -1) ? kSignNegative : kSignPositive;
    }
    else if (is_e(kind(x)))
    {
      s = kSignPositive;
    }
    else if (is_pi(kind(x)))
    {
      s = kSignPositive;
    }
    else if (is_inf(kind(x)))
    {
      s = kSignPositive;
    }
    else if (is_neg_inf(kind(x)))
    {
      s = kSignNegative;
    }
    else if (is_frac(kind(x)))
    {
      s = sign(numerator(x));
    }
    else if (is_var(kind(x)))
    {
      s = kSignPositive;
    }
    else if (is_func(kind(x)))
    {
      s = kSignPositive;
    }
    else if (is_mul(kind(x)))
    {
      s = (compare(constant(x), gConstZero) == -1) ? kSignNegative : kSignPositive;
    }
    else if (is_add(kind(x)))
    {
      s = kSignPositive;
    }
    return s;
  }

  symbol_t opposite(const symbol_t &x)
  {
    return mul(gConstNegOne, x);
  }
}// namespace mysym