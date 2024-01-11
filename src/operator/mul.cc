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
        z = div(gConstOne, mul(pow(x_base, abs(x_exp)), pow(y_base, abs(y_exp))));
      }
      else if ((x_sign == kSignNegative) && (y_sign == kSignPositive))
      {
        symbol_t x_base = base(x);
        z = div(y, pow(x_base, abs(x_exp)));
      }
      else if ((x_sign == kSignPositive) && (y_sign == kSignNegative))
      {
        symbol_t y_base = base(y);
        z = div(x, pow(y_base, abs(y_exp)));
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
        z = div(y, pow(x_base, abs(x_exp)));
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
        z = div(x, pow(y_base, abs(y_exp)));
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
      z = gConstNegInf;
    else if ((is_inf(kind(x))) && (sign(y) == kSignPositive))
      z = gConstInf;
    else if ((is_inf(kind(y))) && (sign(x) == kSignPositive))
      z = gConstInf;
    else if ((is_neg_inf(kind(x))) && (sign(y) == kSignPositive))
      z = gConstNegInf;
    else if ((is_neg_inf(kind(y))) && (sign(x) == kSignPositive))
      z = gConstNegInf;
    else if ((is_inf(kind(x))) && (sign(y) == kSignNegative))
      z = gConstNegInf;
    else if ((is_inf(kind(y))) && (sign(x) == kSignNegative))
      z = gConstNegInf;
    else if ((is_neg_inf(kind(x))) && (sign(y) == kSignNegative))
      z = gConstInf;
    else if ((is_neg_inf(kind(y))) && (sign(x) == kSignNegative))
      z = gConstInf;
    else
      return false;
    return true;
  }

  static symbol_t __mul_num_num(const symbol_t &x, const symbol_t &y)
  {
    number_t f1 = number_t(x.literal);
    number_t f2 = number_t(y.literal);
    return number_to_symbol(f1 * f2);
  }

  static symbol_t __mul_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return compute_frac_num(kOptMul, x, y);
  }

  static symbol_t __mul_num_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_num_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return compute_frac_frac(kOptMul, x, y);
  }

  static symbol_t __mul_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_frac_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_nature_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_nature_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_var_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    symbol_t xb = base(x), yb = base(y);
    symbol_t xe = exponent(x), ye = exponent(y);
    if (compare(xb, yb) == 0)
    {
      z = create(kOptPow);
      append(z, xb);
      symbol_t ze = add(xe, ye);
      append(z, ze);
    }
    else
    {
      if (__handle_pow(x, y, z) == false)
        z = just_make2(kOptMul, x, y);
    }
    return z;
  }

  static symbol_t __mul_log_log(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_func_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x, _y;
    if (is_sym(kind(x)))
    {
      _x = x;
      _y = y;
    }
    else
    {
      _x = y;
      _y = x;
    }
    // return map(_y, _x, kOptMul);
    _y = just_make2(kOptMul, _x, _y);
    play(_y);
    return _y;
    // symbol_t v = create(kOptMul);
    // for (auto it1 = _y.items.begin(); it1 != _y.items.end(); it1++)
    // {
    //   append(v, make(kOptMul, *it1, _x));
    // }
    // return v;
  }

  static symbol_t __mul_sym_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x, _y;
    if (is_sym(kind(x)))
    {
      _x = x;
      _y = y;
    }
    else
    {
      _x = y;
      _y = x;
    }

    _y = just_make2(kOptMul, _x, _y);
    play(_y);
    return _y;
  }

  static symbol_t __mul_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = just_make2(kOptMul, x, y);
    play(z);
    return z;
  }

  static symbol_t __mul_add_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = just_make2(kOptMul, x, y);
    play(z);
    return z;
  }

  static symbol_t __mul_mul_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = just_make2(kOptMul, x, y);
    play(z);
    return z;
  }

  static symbol_t __mul_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    apply_basic_rule(_x);
    return _x;
  }

  static bool __mul_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    //
    // x,y相同的运算
    //
    if (compare(x, y) == 0)
      z = just_make2(kOptPow, x, "2");

    //
    // 与1的运算
    //
    else if (compare(x, gConstOne) == 0)
      z = y;
    else if (compare(y, gConstOne) == 0)
      z = x;

    //
    // 其他情况
    //
    else
      return false;
    return true;
  }

  symbol_t mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = execute_cases(kOptMul, x, y);
    sort(z);
    return z;
  }

  void register_mul_rule()
  {
    // 数值 + xxx
    register_case(kOptMul, make_optsign(kOptNumber, kOptNumber), __mul_num_num);
    register_case(kOptMul, make_optsign(kOptNumber, kOptFrac), __mul_num_frac);
    register_case(kOptMul, make_optsign(kOptNumber, "nature"), __mul_num_nature);
    register_case(kOptMul, make_optsign(kOptNumber, kOptVariate), __mul_num_var);
    register_case(kOptMul, make_optsign(kOptNumber, "func"), __mul_num_func);

    // 分数 + xxx
    register_case(kOptMul, make_optsign(kOptFrac, kOptFrac), __mul_frac_frac);
    register_case(kOptMul, make_optsign(kOptFrac, "nature"), __mul_frac_nature);
    register_case(kOptMul, make_optsign(kOptFrac, kOptVariate), __mul_frac_var);
    register_case(kOptMul, make_optsign(kOptFrac, "func"), __mul_frac_func);

    // 常数 + xxx
    register_case(kOptMul, make_optsign("nature", "nature"), __mul_nature_nature);
    register_case(kOptMul, make_optsign("nature", kOptVariate), __mul_nature_var);
    register_case(kOptMul, make_optsign("nature", "func"), __mul_nature_func);

    // 变量 + xxx
    register_case(kOptMul, make_optsign(kOptVariate, kOptVariate), __mul_var_var);
    register_case(kOptMul, make_optsign(kOptVariate, "func"), __mul_var_func);

    // 特别函数
    register_case(kOptMul, make_optsign(kOptPow, kOptPow), __mul_pow_pow);
    register_case(kOptMul, make_optsign(kOptLog, kOptLog), __mul_log_log);

    // 函数 + xxx
    register_case(kOptMul, make_optsign("func", "func"), __mul_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptMul, make_optsign("sym", kOptMul), __mul_sym_mul);
    register_case(kOptMul, make_optsign("sym", kOptAdd), __mul_sym_add);

    // 多项式 与 单项式
    register_case(kOptMul, make_optsign(kOptMul, kOptMul), __mul_mul_mul);
    register_case(kOptMul, make_optsign(kOptAdd, kOptAdd), __mul_add_add);
    register_case(kOptMul, make_optsign(kOptMul, kOptAdd), __mul_mul_add);

    // 入口
    append_entry(kOptMul, __mul_entry, __mul_preprocess);
  }
} // namespace mysym