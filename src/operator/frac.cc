#include <mysym/mysym.h>
namespace mysym
{
  static symbol_t __reduction(const symbol_t &x, const symbol_t y)
  {
    return just_make2(kOptFrac, x, y);
  }

  symbol_t frac_entry(const symbol_t &x)
  {
    symbol_t n = numerator(x), d = denominator(x);
    symbol_t y;
    if (is_num(kind(n)) && is_num(kind(d)))
    {
      y = __reduction(n, d);
    }
    else if (is_num(kind(n)) && !is_num(kind(d)))
    {
      apply_rule(d);
      y = just_make2(kOptMul, n, just_make2(kOptPow, d, gConstNegOne));
    }
    else if (!is_num(kind(n)) && is_num(kind(d)))
    {
      apply_rule(n);
      y = just_make2(kOptMul, just_make2(kOptFrac, gConstOne, d), n);
    }
    else if (!is_num(kind(n)) && !is_num(kind(d)))
    {
      apply_rule(n);
      apply_rule(d);
      y = just_make2(kOptMul, n, just_make2(kOptPow, d, gConstNegOne));
    }
    return y;
  }

  symbol_t frac(const symbol_t &x, const symbol_t &y)
  {
    return default_func_handler(kOptFrac, x, y);
  }
} // namespace mysym