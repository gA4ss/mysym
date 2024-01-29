#include <mysym/mysym.h>

namespace mysym
{
  static symbol_t __log(const symbol_t &b, const symbol_t &e)
  {
    // symbol_t b = base(x), e = exponent(x);

    //
    // 指数与底相同
    //
    if (compare(b, e) == 0)
    {
      return gConstOne;
    }

    //
    // 指数 : (0, 正无穷)
    //
    if (compare(e, gConstZero) == 0)
    {
      return gConstNegInf;
    }
    else if (compare(e, gConstOne) == 0)
    {
      return gConstZero;
    }
    else if (compare(e, gConstNegOne) == 0)
    {
      // 异常
    }
    else if (compare(e, gConstInf) == 0)
    {
      return gConstInf;
    }
    else if (compare(e, gConstNegInf) == 0)
    {
      // 异常
    }

    //
    // 底 : 大于零且不等于1
    //
    if (compare(b, gConstZero) == 0)
    {
      // 异常
    }
    else if (compare(b, gConstOne) == 0)
    {
      // 异常
    }
    else if (compare(b, gConstNegOne) == 0)
    {
      // 异常
    }
    else if (compare(b, gConstInf) == 0)
    {
      return gConstInf;
    }
    else if (compare(b, gConstNegInf) == 0)
    {
      // 异常
    }
    return just_make2(kOptLog, b, e);
  }

  static bool __log_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    //
    // 检查定义域
    //
    if (is_const(kind(y)))
    {
      // 指数要大于0
      if (compare(y, gConstZero) != 1)
      {
        mysym_the_domain_of_definition_is_out_of_range_exception(
          "exponent must greater than 0, y = %s", print_string(y).c_str());
      }
    }

    if (is_const(kind(x)))
    {
      // 真数要大于0并且不能等于1
      if ((compare(x, gConstZero) < 1) && (compare(x, gConstOne) == 0))
      {
        mysym_the_domain_of_definition_is_out_of_range_exception(
          "antilog must greater than 0 and not equal 1, x = %s", print_string(x).c_str());
      }
    }
    return false;
  }

  static symbol_t __log_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  symbol_t log(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptLog, x, y);
  }

  void register_log_rule()
  {
    register_case(kOptLog, make_optsign("all", "all"), __log);

    // 预处理与后置处理
    register_preprocess(kOptLog, __log_preprocess);
    register_postprocess(kOptLog, __log_postprocess);
  }
} // namespace mysym