#include <mysym/mysym.h>
#include <mynum/wrapper.h>
#include "__test.h"

namespace mysym
{
  static symbol_t __add_num_num(const symbol_t &x, const symbol_t &y)
  {
    number_t f1 = number_t(x.literal);
    number_t f2 = number_t(y.literal);
    return number_to_symbol(f1 + f2);
  }

  static symbol_t __add_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return compute_frac_num(kOptAdd, x, y);
  }

  static symbol_t __add_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_num_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return compute_frac_frac(kOptAdd, x, y);
  }

  static symbol_t __add_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  #include "__add_log.cc"

  static symbol_t __add_func_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_sym_add(const symbol_t &x, const symbol_t &y)
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

    _y = just_make2(kOptAdd, _x, _y);
    play(_y);
    return _y;
  }

  static symbol_t __add_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return just_make2(kOptMul, create_int("2"), x);
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_add_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = c_add(x, y);
    combine_like_terms(z);
    return z;
  }

  static symbol_t __add_mul_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = c_add(x, y);
    apply_rule(z);
    return z;
  }

  static symbol_t __add_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    apply_basic_rule(_x);
    return _x;
  }

  static bool __add_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    //
    // x,y相同的运算
    //
    if (compare(x, y) == 0)
    {
      z = just_make2(kOptMul, "2", x);
    }
    
    //
    // 与0的运算
    //
    else if (compare(x, gConstZero) == 0)
      z = y;
    else if (compare(y, gConstZero) == 0)
      z = x;

    //
    // 对♾️的相关计算
    //
    else if (__test_and_or(is_inf, is_neg_inf, x, y))
      z = gConstZero;
    else if (__test_or(is_inf, x, y))
      z = gConstInf;
    else if (__test_or(is_neg_inf, x, y))
      z = gConstNegInf;
    
    //
    // 错误情况
    //
    else
      return false;
    return true;
  }

  symbol_t add(const symbol_t &x, const symbol_t &y)
  {
    //
    // 1. 如果x符号为正，y符号为正，则正常运算。
    // 2. 如果x符号为正，y符号为负，则转为减法运算。
    // 3. 如果x符号为负，y符号为正，则转为减法运算y-x。
    // 4. 如果x符号为负，y符号为负，则提出-1并进行-1 * (x+y)。
    //
    symbol_t z;
    int sign_x = sign(x), sign_y = sign(y);
    if ((sign_x == kSignPositive) && (sign_y == kSignPositive))
    {
      z = execute_cases(kOptAdd, x, y);
    }
    else if ((sign_x == kSignPositive) && (sign_y == kSignNegative))
    {
      z = execute_cases(kOptSub, x, abs(y));
    }
    else if ((sign_x == kSignNegative) && (sign_y == kSignPositive))
    {
      z = execute_cases(kOptSub, y, abs(x));
    }
    else // if ((sign_x == kSignNegative) && (sign_y == kSignNegative))
    {
      z = execute_cases(kOptAdd, abs(x), abs(y));
      z = just_make2(kOptMul, gConstNegOne, x);
    }
    sort(z);
    return z;
  }

  void register_add_rule()
  {
    // 数值 + xxx
    register_case(kOptAdd, make_optsign(kOptNumber, kOptNumber), __add_num_num);
    register_case(kOptAdd, make_optsign(kOptNumber, kOptFrac), __add_num_frac);
    register_case(kOptAdd, make_optsign(kOptNumber, "nature"), __add_num_nature);
    register_case(kOptAdd, make_optsign(kOptNumber, kOptVariate), __add_num_var);
    register_case(kOptAdd, make_optsign(kOptNumber, "func"), __add_num_func);

    // 分数 + xxx
    register_case(kOptAdd, make_optsign(kOptFrac, kOptFrac), __add_frac_frac);
    register_case(kOptAdd, make_optsign(kOptFrac, "nature"), __add_frac_nature);
    register_case(kOptAdd, make_optsign(kOptFrac, kOptVariate), __add_frac_var);
    register_case(kOptAdd, make_optsign(kOptFrac, "func"), __add_frac_func);

    // 常数 + xxx
    register_case(kOptAdd, make_optsign("nature", "nature"), __add_nature_nature);
    register_case(kOptAdd, make_optsign("nature", kOptVariate), __add_nature_var);
    register_case(kOptAdd, make_optsign("nature", "func"), __add_nature_func);

    // 变量 + xxx
    register_case(kOptAdd, make_optsign(kOptVariate, kOptVariate), __add_var_var);
    register_case(kOptAdd, make_optsign(kOptVariate, "func"), __add_var_func);

    // 特别函数
    register_case(kOptAdd, make_optsign(kOptPow, kOptPow), __add_pow_pow);
    register_case(kOptAdd, make_optsign(kOptLog, kOptLog), __add_log_log);

    // 函数 + xxx
    register_case(kOptAdd, make_optsign("func", "func"), __add_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptAdd, make_optsign("sym", kOptMul), __add_sym_mul);
    register_case(kOptAdd, make_optsign("sym", kOptAdd), __add_sym_add);

    // 多项式 与 单项式
    register_case(kOptAdd, make_optsign(kOptMul, kOptMul), __add_mul_mul);
    register_case(kOptAdd, make_optsign(kOptAdd, kOptAdd), __add_add_add);
    register_case(kOptAdd, make_optsign(kOptMul, kOptAdd), __add_mul_add);

    // 入口
    append_entry(kOptAdd, __add_entry, __add_preprocess);
  }
} // namespace mysym