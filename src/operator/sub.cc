#include <mysym/mysym.h>
#include <mynum/wrapper.h>
#include "__test.h"

namespace mysym
{
  static bool __handle_sign(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    //
    // 1. 如果x符号为正，y符号为负，则转为减法运算。
    // 2. 如果x符号为负，y符号为正，则转为减法运算y-x。
    // 3. 如果x符号为负，y符号为负，则提出-1并进行-1 * (x+y)。
    // 4. 如果x符号为正，y符号为正，则正常运算。
    //
    int sign_x = sign(x), sign_y = sign(y);
    if ((sign_x == kSignPositive) && (sign_y == kSignNegative))
    {
      z = execute_cases(kOptAdd, x, abs(y));
    }
    else if ((sign_x == kSignNegative) && (sign_y == kSignPositive))
    {
      z = execute_cases(kOptAdd, abs(x), y);
      z = mul(gConstOne, z);
    }
    else if ((sign_x == kSignNegative) && (sign_y == kSignNegative))
    {
      z = execute_cases(kOptSub, abs(y), abs(x));
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
    if (is_inf(kind(x)) && is_neg_inf(kind(y)))
      z = gConstInf;
    else if (is_neg_inf(kind(x)) && is_inf(kind(y)))
      z = gConstNegInf;
    else if (is_inf(kind(x)))
      z = gConstInf;
    else if (is_inf(kind(y)))
      z = gConstNegInf;
    else if (is_neg_inf(kind(x)))
      z = gConstNegInf;
    else if (is_neg_inf(kind(y)))
      z = gConstInf;
    else
      return false;
    return true;
  }

  static symbol_t __sub_num_num(const symbol_t &x, const symbol_t &y)
  {
    number_t f1 = number_t(x.literal);
    number_t f2 = number_t(y.literal);
    return number_to_symbol(f1 - f2);
  }

  static symbol_t __sub_num_frac(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = compute_frac_num(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_num_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_num_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_num_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = compute_frac_frac(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_frac_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_frac_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_nature_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_nature_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_var_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_var_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_log_log(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    symbol_t xb = base(x), yb = base(y);
    symbol_t xe = exponent(x), ye = exponent(y);
    if (compare(xb, yb) == 0)
    {
      z = create(kOptLog);
      append(z, xb);
      symbol_t ze = div(xe, ye);
      append(z, ze);
    }
    else
    {
      if (__handle_sign(x, y, z) == false)
        z = just_make2(kOptSub, x, y);
    }
    return z;
  }

  static symbol_t __sub_func_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_sym_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x, _y, z;
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

    if (__handle_sign(_x, _y, z) == false)
      z = just_make2(kOptSub, x, y);
    play(z);
    return z;
  }

  static symbol_t __sub_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_add_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = c_sub(x, y);
    combine_like_terms(z);
    return z;
  }

  static symbol_t __sub_mul_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = c_sub(x, y);
    apply_rule(z);
    return z;
  }

  static symbol_t __sub_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    apply_basic_rule(_x);
    return _x;
  }

  static bool __sub_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    //
    // x,y相同的运算
    //
    if (compare(x, y) == 0)
      z = gConstZero;

    //
    // 与0的运算
    //
    else if (compare(x, gConstZero) == 0)
      z = opposite(y);
    else if (compare(y, gConstZero) == 0)
      z = x;

    //
    // 错误情况
    //
    else
      return false;
    return true;
  }

  symbol_t sub(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = execute_cases(kOptSub, x, y);
    sort(z);
    return z;
  }

  void register_sub_rule()
  {
    // 数值 + xxx
    register_case(kOptSub, make_optsign(kOptNumber, kOptNumber), __sub_num_num);
    register_case(kOptSub, make_optsign(kOptNumber, kOptFrac), __sub_num_frac);
    register_case(kOptSub, make_optsign(kOptNumber, "nature"), __sub_num_nature);
    register_case(kOptSub, make_optsign(kOptNumber, kOptVariate), __sub_num_var);
    register_case(kOptSub, make_optsign(kOptNumber, "func"), __sub_num_func);

    // 分数 + xxx
    register_case(kOptSub, make_optsign(kOptFrac, kOptFrac), __sub_frac_frac);
    register_case(kOptSub, make_optsign(kOptFrac, "nature"), __sub_frac_nature);
    register_case(kOptSub, make_optsign(kOptFrac, kOptVariate), __sub_frac_var);
    register_case(kOptSub, make_optsign(kOptFrac, "func"), __sub_frac_func);

    // 常数 + xxx
    register_case(kOptSub, make_optsign("nature", "nature"), __sub_nature_nature);
    register_case(kOptSub, make_optsign("nature", kOptVariate), __sub_nature_var);
    register_case(kOptSub, make_optsign("nature", "func"), __sub_nature_func);

    // 变量 + xxx
    register_case(kOptSub, make_optsign(kOptVariate, kOptVariate), __sub_var_var);
    register_case(kOptSub, make_optsign(kOptVariate, "func"), __sub_var_func);

    // 特别函数
    register_case(kOptSub, make_optsign(kOptPow, kOptPow), __sub_pow_pow);
    register_case(kOptSub, make_optsign(kOptLog, kOptLog), __sub_log_log);

    // 函数 + xxx
    register_case(kOptSub, make_optsign("func", "func"), __sub_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptSub, make_optsign("sym", kOptMul), __sub_sym_mul);
    register_case(kOptSub, make_optsign("sym", kOptAdd), __sub_sym_add);

    // 多项式 与 单项式
    register_case(kOptSub, make_optsign(kOptMul, kOptMul), __sub_mul_mul);
    register_case(kOptSub, make_optsign(kOptAdd, kOptAdd), __sub_add_add);
    register_case(kOptSub, make_optsign(kOptMul, kOptAdd), __sub_mul_add);

    // 入口
    append_entry(kOptSub, __sub_entry, __sub_preprocess);
  }
} // namespace mysym