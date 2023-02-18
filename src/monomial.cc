#include <mysym/mysym.h>

namespace mysym
{
  bool is_monomial(const symbol_t &s, const symbol_t &x)
  {
    // s是一个常数。
    if (is_num(kind(s)))
      return true;

    // s是一个变量并且等于x
    if (is_var(kind(s)))
      return match(s, x);

    // s是一个分数，但是分子是单项式，分母是常数。
    if (kind(s) == kOptFrac)
    {
      return ((is_num(kind(denominator(s)))) && is_monomial(numerator(s), x)) ? true : false;
    }

    // s是变量x的某次幂，其中指数是整数。
    // 这里指数只规定是整数
    if (kind(s) == kOptPow)
    {
      if ((is_int(kind(s.items[1]))) && (is_var(kind(s.items[0]))))
      {
        return match(s.items[0], x);
      }
    }

    // s是一个积，是满足以上条件项的乘积。
    if (kind(s) == kOptMul)
    {
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
        if (!is_monomial(*it, x))
          return false;
      }
      return true;
    }

    return false;
  }
} // namespace mysym