#include <mysym/mysym.h>
#include <mynum/wrapper.h>
#include "__test.h"

namespace mysym
{
// x,y相同的运算
#define __x_equ_y(x, y) {               \
  if (compare(x, y) == 0)               \
    return just_make2(kOptPow, x, "2"); \
}

//
// 与1的运算
//
#define __calculate_with_one(x, y) {    \
  if (compare(x, gConstOne) == 0)       \
    return y;                           \
  else if (compare(y, gConstOne) == 0)  \
    return x;                           \
}

//
// 对♾️的相关计算
//
#define __calculate_with_infinite(x, y) {                           \
  if (__test_and_or(is_inf, is_neg_inf, x, y)) return gConstNegInf; \
  else if (__test_or(is_inf, x, y)) return gConstInf;               \
  else if (__test_or(is_neg_inf, x, y)) return gConstNegInf;        \
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
    __compare_one(x, y);
    __calculate_with_infinite(x, y);
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_num_var(const symbol_t &x, const symbol_t &y)
  {
    __compare_one(x, y);
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_num_func(const symbol_t &x, const symbol_t &y)
  {
    __compare_one(x, y);
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    __x_equ_y(x, y);
    return compute_frac_frac(kOptMul, x, y);
  }

  static symbol_t __mul_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    __calculate_with_infinite(x, y);
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
    {
      if (is_inf(kind(x)))
        return gConstInf;
      else if (is_neg_inf(kind(x)))
        return gConstInf;
      else
        return just_make2(kOptPow, x, "2");
    }

    __calculate_with_infinite(x, y);
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_var_var(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return just_make2(kOptPow, x, "2");
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  #include "__mul_pow.cc"

  static symbol_t __mul_log_log(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return just_make2(kOptPow, x, "2");
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_func_func(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return just_make2(kOptPow, x, "2");
    return just_make2(kOptMul, x, y);
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
    if (compare(x, y) == 0)
      return c_pow(x, "2");
    symbol_t z = just_make2(kOptMul, x, y);
    play(z);
    return z;
  }

  static symbol_t __mul_add_add(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return just_make2(kOptPow, x, create_int("2"));
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

  symbol_t mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = execute_cases(kOptMul, x, y);
    // 整理结果
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
    append_entry(kOptMul, __mul_entry);
  }
} // namespace mysym