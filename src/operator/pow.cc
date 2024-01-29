#include <mysym/mysym.h>

namespace mysym
{
  static bool __test_exponent(const symbol_t &b, const symbol_t &e, symbol_t &x)
  {
    //
    // 指数 : 0, 1, -1, 无穷，负无穷
    //
    if (compare(e, gConstZero) == 0)
    {
      x = gConstOne;
      return true;
    }
    else if (compare(e, gConstOne) == 0)
    {
      x = b;
      return true;
    }
    else if (compare(e, gConstNegOne) == 0)
    {
      if (is_num(kind(b)))
      {
        x = frac(gConstOne, just_make2(kOptPow, b, e));
        return true;
      }
    }
    else if (compare(e, gConstInf) == 0)
    {
      //
      // 确定不了变量的符号，所以这里保留。
      //
      x = gConstUDF;
    }
    else if (compare(e, gConstNegInf) == 0)
    {
      //
      // 无论底的符号是啥，最终都趋于0。
      //
      x = gConstZero;
      return true;
    }

    x = gConstUDF;
    return false;
  }

  static bool __test_base(const symbol_t &b, const symbol_t &e, symbol_t &x)
  {
    //
    // 底 : 0, 1, -1, 无穷，负无穷
    //
    if (compare(b, gConstZero) == 0)
    {
      x = gConstZero;
      return true;
    }
    else if (compare(b, gConstOne) == 0)
    {
      x = gConstOne;
      return true;
    }
    else if (compare(b, gConstNegOne) == 0)
    {
      if (is_num(kind(e)))
      {
        if (compare(mod(e, create_int("2")), gConstZero) == 0)
          x = gConstOne;
        else
          x = gConstNegOne;
        return true;
      }
    }
    else if (compare(b, gConstInf) == 0)
    {
      if (is_num(kind(e)))
      {
        if (compare(e, gConstZero) < 0)
          x = gConstZero;
        else if (compare(e, gConstZero) > 0)
          x = gConstInf;
        return true;
      }
    }
    else if (compare(b, gConstNegInf) == 0)
    {
      if (is_num(kind(e)))
      {
        if (compare(e, gConstZero) < 0)
        {
          x = gConstZero;
          return true;
        }
        else if (compare(e, gConstZero) > 0)
        {
          if (compare(mod(e, create_int("2")), gConstZero) == 0)
            x = gConstInf;
          else
            x = gConstNegInf;
          return true;
        }
      } /* end if */
    }

    x = gConstUDF;
    return false;
  }

  static symbol_t __pow(const symbol_t &b, const symbol_t &e)
  {
    // symbol_t b = base(x), e = exponent(x);
    symbol_t x;
    if (__test_exponent(b, e, x))
      return x;
    if (__test_base(b, e, x))
      return x;
    return just_make2(kOptPow, b, e);
  }

  static bool __pow_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __pow_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;

    // 检查值域

    sort(_z);
    return _z;
  }

  symbol_t pow(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptPow, x, y);
  }

  void register_pow_rule()
  {
    register_case(kOptPow, make_optsign("all", "all"), __pow);

    // 预处理与后置处理
    register_preprocess(kOptPow, __pow_preprocess);
    register_postprocess(kOptPow, __pow_postprocess);
  }
} // namespace mysym