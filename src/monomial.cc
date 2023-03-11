#include <mysym/mysym.h>

namespace mysym
{
  bool is_monomial(const symbol_t &s, const symbol_t &x)
  {
    //
    // 检查参数
    //
    if (!is_var(kind(x)))
    {
      mysym_invalid_param_type_exception("it's must be variate type, it's %d.", kind(x));
    }

    // s是一个常数。x^0
    if (is_const(kind(s)))
      return true;

    // s是一个变量并且等于x
    if (is_var(kind(s)))
      return (cmp(s, x) == 0);

    //
    // 这里保留之前的一段代码，之前的代码允许在分数
    // 形式中出现符号，后修订为分数不能存在符号，所
    // 有带分数的符号必须转换成幂的形式。
    // s是一个分数，但是分子是单项式，分母是常数。
    // if (kind(s) == kOptFrac)
    // {
    //   return ((is_num(kind(denominator(s)))) && is_monomial(numerator(s), x)) ? true : false;
    // }

    // s是变量x的某次幂，其中指数是整数。
    // 这里指数只规定是整数
    if (kind(s) == kOptPow)
    {
      if ((is_int(kind(s.items[1]))) && (is_var(kind(s.items[0]))))
      {
        return (cmp(s.items[0], x) == 0);
      }
    }

    //
    // s是一个积，是满足以上条件项的乘积。
    // 这里蕴含了，只能是一个常量与一个符号的变量相乘。
    if ((kind(s) == kOptMul) && (symbol_size(s) == 2))
    {
      return is_monomial(operand(s, 0), x) && is_monomial(operand(s, 1), x);
    }

    return false;
  }

  bool is_monomial(const symbol_t &s, const list_t &xs)
  {
    check_list_all_variate_type(xs);

    if (is_const(kind(s)))
      return true;

    if (is_var(kind(s)))
    {
      return find(xs, s);
    }

    if (is_pow(kind(s)))
    {
      if (is_int(kind(exponent(s))))
      {
        return find(xs, base(s));
      }
      return false;
    }

    if (is_mul(kind(s)))
    {
      for (auto is = s.items.begin(); is != s.items.end(); is++)
      {
        if (is_const(kind(*is)))
          continue;

        if (is_var(kind(*is)))
        {
          return find(xs, *is);
        }
        else if (is_pow(kind((*is))))
        {
          if (is_int(kind(exponent(*is))))
          {
            return find(xs, base(*is));
          }
        }
      }
    }

    return false;
  }
} // namespace mysym