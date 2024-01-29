#include <mysym/mysym.h>
#include <mynum/wrapper.h>
#include "__test.h"

namespace mysym
{
  //
  // 本函数仅在xxx_func中使用
  //
  static bool __handle_pow(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    if (is_pow(kind(x)) && is_pow(kind(y)))
    {
      symbol_t x_exp = exponent(x), y_exp = exponent(y);
      int x_sign = sign(exponent(x)), y_sign = sign(exponent(y));

      if ((x_sign == kSignNegative) && (y_sign == kSignNegative))
      {
        symbol_t x_base = base(x), y_base = base(y);
        z = div(pow(y_base, abs(y_exp)), pow(x_base, abs(x_exp)));
      }
      else if ((x_sign == kSignNegative) && (y_sign == kSignPositive))
      {
        symbol_t x_base = base(x);
        z = div(gConstOne, mul(pow(x_base, abs(x_exp)), y));
      }
      else if ((x_sign == kSignPositive) && (y_sign == kSignNegative))
      {
        symbol_t y_base = base(y);
        z = mul(x, pow(y_base, abs(y_exp)));
      }
      else // ((x_sign == kSignPositive) && (y_sign == kSignPositive))
      {
        return false;
      }
    }
    else if (is_pow(kind(x)))
    {
      symbol_t x_exp = exponent(x);
      int x_sign = sign(exponent(x));

      if (x_sign == kSignNegative)
      {
        symbol_t x_base = base(x);
        z = div(gConstOne, mul(pow(x_base, abs(x_exp)), y));
      }
      else
      {
        return false;
      }
    }
    else if (is_pow(kind(y)))
    {
      symbol_t y_exp = exponent(y);
      int y_sign = sign(exponent(y));

      if (y_sign == kSignNegative)
      {
        symbol_t y_base = base(y);
        z = mul(x, pow(y_base, abs(y_exp)));
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
    return true;
  }

  static bool __handle_infinity(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    //
    // 对♾️的相关计算
    //
    if (__test_and_or(is_inf, is_neg_inf, x, y))
      z = gConstNegOne;
    else if ((is_inf(kind(x))) && (sign(y) == kSignPositive))
      z = gConstInf;
    else if ((is_inf(kind(x))) && (sign(y) == kSignNegative))
      z = gConstNegInf;
    else if ((is_inf(kind(y))) || (is_neg_inf(kind(y))))
      z = gConstZero;
    else
      return false;
    return true;
  }

  static bool __handle_dividend_one(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    if (compare(x, gConstOne) == 0)
    {
      z = pow(y, gConstNegOne);
      return true;
    }
    return false;
  }

  static symbol_t __div_num_num(const symbol_t &x, const symbol_t &y)
  {
    // 如果是整型，需要转换成浮点数才能得到浮点结果，否则是整型。
    number_t f1 = mynum::integer_to_float(number_t(x.literal));
    number_t f2 = mynum::integer_to_float(number_t(y.literal));
    return number_to_symbol(f1 / f2);
  }

  static symbol_t __div_num_frac(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, gConstOne) == 0)
    {
      symbol_t n = numerator(y), d = denominator(y);
      return frac(d, n);
    }
    return compute_frac_num(kOptDiv, x, y);
  }

  static symbol_t __div_num_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    if (__handle_dividend_one(x, y, z) == true)
      return z;
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_num_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_dividend_one(x, y, z) == true)
      return z;
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_num_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_dividend_one(x, y, z) == true)
      return z;
    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptDiv, x, y);
    return z;
  }

  static symbol_t __div_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return compute_frac_frac(kOptDiv, x, y);
  }

  static symbol_t __div_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_frac_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptDiv, x, y);
    return z;
  }

  static symbol_t __div_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_nature_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_nature_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptDiv, x, y);
    return z;
  }

  static symbol_t __div_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_var_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptDiv, x, y);
    return z;
  }

  static symbol_t __div_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    symbol_t xb = base(x), yb = base(y);
    symbol_t xe = exponent(x), ye = exponent(y);
    if (compare(xb, yb) == 0)
    {
      z = create(kOptPow);
      append(z, xb);
      symbol_t ze = sub(xe, ye);
      append(z, ze);
    }
    else
    {
      if (__handle_pow(x, y, z) == false)
        z = just_make2(kOptDiv, x, y);
    }
    return z;
  }

  static symbol_t __div_log_log(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_func_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptDiv, x, y);
    return z;
  }

  //////////////////////////////////////////////////
  // 这里进入单个符号与单项式与多项式的处理
  //////////////////////////////////////////////////

#include "__polynomial_div.cc"

  static symbol_t __div_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t n, d, z;
    if (is_sym(kind(x)))
    {
      __polynomial_div_sym_mul(x, y, n, d);
    }
    else
    {
      __polynomial_div_mul_sym(x, y, n, d);
    }

    if (compare(d, gConstOne) == 0)
      z = n;
    else
      z = just_make2(kOptDiv, n, d);
    return z;
  }

  static symbol_t __div_sym_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t n, d, z;
    if (is_sym(kind(x)))
    {
      __polynomial_div_sym_add(x, y, n, d);
    }
    else
    {
      __polynomial_div_add_sym(x, y, n, d);
    }

    if (compare(d, gConstOne) == 0)
      z = n;
    else
      z = just_make2(kOptDiv, n, d);
    return z;
  }

  static symbol_t __div_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_add_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  static bool __div_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    //
    // 除数为0
    //
    if (compare(y, gConstZero) == 0)
    {
      mysym_the_divisor_is_zero_exception("%s", "y == 0");
    }

    //
    // x,y相同的运算
    //
    if (compare(abs(x), abs(y)) == 0)
    {
      if ((sign(x) != sign(y)))
        z = gConstNegOne;
      else
        z = gConstOne;
    }

    //
    // 被除数为0
    // 除数为1或者-1
    //
    else if (compare(x, gConstZero) == 0)
      z = gConstZero;
    else if (compare(y, gConstOne) == 0)
      z = x;
    else if (compare(y, gConstNegOne) == 0)
      z = opposite(x);

    //
    // 其他情况
    //
    else
      return false;
    return true;
  }

  static symbol_t __div_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    if (is_normal(kind(_z)))
    {
      // 基础单元运算都是二元运算
      if (size(_z) == 1)
      {
        _z = _z[0];
      }
    }
    sort(_z);
    return _z;
  }

  symbol_t div(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptDiv, x, y);
  }

  void register_div_rule()
  {
    // 数值 / xxx
    register_case(kOptDiv, make_optsign(kOptNumber, kOptNumber), __div_num_num);
    register_case(kOptDiv, make_optsign(kOptNumber, kOptFrac), __div_num_frac);
    register_case(kOptDiv, make_optsign(kOptNumber, "nature"), __div_num_nature);
    register_case(kOptDiv, make_optsign(kOptNumber, kOptVariate), __div_num_var);
    register_case(kOptDiv, make_optsign(kOptNumber, "func"), __div_num_func);

    // 分数 / xxx
    register_case(kOptDiv, make_optsign(kOptFrac, kOptFrac), __div_frac_frac);
    register_case(kOptDiv, make_optsign(kOptFrac, "nature"), __div_frac_nature);
    register_case(kOptDiv, make_optsign(kOptFrac, kOptVariate), __div_frac_var);
    register_case(kOptDiv, make_optsign(kOptFrac, "func"), __div_frac_func);

    // 常数 / xxx
    register_case(kOptDiv, make_optsign("nature", "nature"), __div_nature_nature);
    register_case(kOptDiv, make_optsign("nature", kOptVariate), __div_nature_var);
    register_case(kOptDiv, make_optsign("nature", "func"), __div_nature_func);

    // 变量 / xxx
    register_case(kOptDiv, make_optsign(kOptVariate, kOptVariate), __div_var_var);
    register_case(kOptDiv, make_optsign(kOptVariate, "func"), __div_var_func);

    // 特别函数
    register_case(kOptDiv, make_optsign(kOptPow, kOptPow), __div_pow_pow);
    register_case(kOptDiv, make_optsign(kOptLog, kOptLog), __div_log_log);

    // 函数 / xxx
    register_case(kOptDiv, make_optsign("func", "func"), __div_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptDiv, make_optsign("sym", kOptMul), __div_sym_mul);
    register_case(kOptDiv, make_optsign("sym", kOptAdd), __div_sym_add);

    // 多项式 与 单项式
    register_case(kOptDiv, make_optsign(kOptMul, kOptMul), __div_mul_mul);
    register_case(kOptDiv, make_optsign(kOptAdd, kOptAdd), __div_add_add);
    register_case(kOptDiv, make_optsign(kOptMul, kOptAdd), __div_mul_add);

    // 预处理与后置处理
    register_preprocess(kOptDiv, __div_preprocess);
    register_postprocess(kOptDiv, __div_postprocess);
  }
} // namespace mysym