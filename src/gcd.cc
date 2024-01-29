#include <mysym/mysym.h>

namespace mysym
{

  symbol_t gcd_integer(const int_t &x, const int_t &y)
  {
    if (symbol_is_integer(x) && symbol_is_integer(y))
    {
      symbol_t g;
      return g;
    }
    return gConstUDF;
  }

  symbol_t gcd_polynomial_items(const symbol_t &x)
  {
    if (!is_add(kind(x)))
      return gConstUDF;
    
    list_t tl = terms(x);

    size_t n = size(cl);
    return gConstUDF;
  }

  symbol_t gcd_polynomial_coefficient(const symbol_t &x)
  {
    if (!is_add(kind(x)))
      return gConstUDF;

    list_t cl = coefficients(x);
    size_t n = size(cl);
    
    if (n == 0)
      return gConstUDF;
    else if (n == 1)
      return cl[0];
  
    symbol_t g = cl[0];
    for (size_t i = 1; i < n; i++)
    {
      g = gcd_integer(g, l[i]);
      if (compare(g, gConstUDF) == 0)
        break;
    }
    return g;
  }

  // 这个函数主要计算单项式得公约数
  static symbol_t __gcd(const symbol_t &x, const symbol_t &y)
  {
    if (symbol_is_integer(x) && symbol_is_integer(y))
    {

    }

    return gConstUDF;
  }

  symbol_t gcd(const symbol_t &x)
  {
    if (!(is_add(kind(x)) || is_mul(kind(x))))
      return gConstUDF;

    size_t n = size(x);
    if (n == 0)
      return gConstUDF;

    const symbol_t &l = x.items;
    const symbol_t &g = l[0];
    for (size_t i = 1; i < n; i++)
    {
      g = __gcd(g, l[i]);
    }
    return g;
  }

  symbol_t gcd(const symbol_t &x, symbol_t &l)
  {
    return gConstUDF;
  }

  symbol_t gcd(const list_t &s)
  {
    return gConstUDF;
  }

  symbol_t gcd(const list_t &s, list_t &l)
  {
    return gConstUDF;
  }
} // namespace mysym