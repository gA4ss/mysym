#include <mysym/mysym.h>
namespace mysym
{
  static bool __frac_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __frac_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  static symbol_t __reduction(const symbol_t &n, const symbol_t &d)
  {
    return just_make2(kOptFrac, n, d);
  }

  static symbol_t __frac(const symbol_t &n, const symbol_t &d)
  {
    // symbol_t n = numerator(x), d = denominator(x);
    symbol_t f;
    if (is_num(kind(n)) && is_num(kind(d)))
    {
      f = __reduction(n, d);
    }
    else if (is_num(kind(n)) && !is_num(kind(d)))
    {
      f = mul(n, pow(d, gConstNegOne));
    }
    else if (!is_num(kind(n)) && is_num(kind(d)))
    {
      f = mul(just_make2(kOptFrac, gConstOne, d), n);
    }
    else if (!is_num(kind(n)) && !is_num(kind(d)))
    {
      f = mul(pow(d, gConstNegOne), n);
    }
    return f;
  }

  symbol_t frac(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptFrac, x, y);
  }

  void register_frac_rule()
  {
    register_case(kOptFrac, make_optsign("all", "all"), __frac);

    // 添加预处理与置后处理
    register_preprocess(kOptFrac, __frac_preprocess);
    register_postprocess(kOptFrac, __frac_postprocess);
  }
} // namespace mysym