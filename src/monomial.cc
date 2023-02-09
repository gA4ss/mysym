#include <mysym/mysym.h>

namespace mysym
{
  bool is_monomial(const symbol_t& s)
  {
    // s是一个常数。
    // s是一个变量。
    // s是一个分数，但是分子是单项式，分母是常数。
    // s是一个变量的某次幂，其中指数是整数。
    // s是一个积，是满足以上条件项的乘积。

    if (is_sym(kind(s)))
      return true;
    
    if (kind(s) == kOptFrac)
    {
      return ((is_num(kind(denominator(s)))) && is_monomial(numerator(s))) ? true : false;
    }

    if (kind(s) == kOptPow)
    {
      return ((is_num(kind(s.items[1]))) && (is_sym(kind(s.items[0])))) ? true : false;
    }

    if (kind(s) == kOptMul)
    {
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
        if (!is_monomial(*it))
          return false;
      }
      return true;
    }

    return false;
  }
} // namespace mysym