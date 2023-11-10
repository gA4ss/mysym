#include <mysym/mysym.h>
#include <mynum/wrapper.h>
#include "__test.h"

namespace mysym
{
  static symbol_t __div_num_num(const symbol_t &x, const symbol_t &y)
  {
    // 如果是整型，需要转换成浮点数才能得到浮点结果，否则是整型。
    number_t f1 = mynum::integer_to_float(number_t(x.literal));
    number_t f2 = mynum::integer_to_float(number_t(y.literal));
    return number_to_symbol(f1 / f2);
  }

  static symbol_t __div_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return compute_frac_num(kOptDiv, x, y);
  }

  static symbol_t __div_num_nature(const symbol_t &x, const symbol_t &y)
  {
    if (compare(y, gConstOne) == 0)
      return x;
    else if (compare(y, gConstNegOne) == 0)
      return opposite(x);
    if (compare(y, gConstZero) == 0)
    {
      // 发生异常，除数不能为0
    }
    return make(kOptDiv, x, y);
  }

  static symbol_t __div_num_var(const symbol_t &x, const symbol_t &y)
  {
    if (compare(y, gConstOne) == 0)
      return x;
    else if (compare(y, gConstNegOne) == 0)
      return opposite(x);
    if (compare(y, gConstZero) == 0)
    {
      // 发生异常，除数不能为0
    }
    return make(kOptDiv, x, y);
  }

  static symbol_t __div_num_func(const symbol_t &x, const symbol_t &y)
  {
    if (compare(y, gConstOne) == 0)
      return x;
    else if (compare(y, gConstNegOne) == 0)
      return opposite(x);
    if (compare(y, gConstZero) == 0)
    {
      // 发生异常，除数不能为0
    }
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return compute_frac_frac(kOptDiv, x, y);
  }

  static symbol_t __div_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return gConstOne;

    //
    // 对♾️的计算
    //
    if (__test_and_or(is_inf, is_neg_inf, x, y))
      return gConstNegOne;
    else if (__test_opt(kOptConstInf, x))
      return gConstInf;
    else if (__test_opt(kOptConstInf, y))
      return gConstZero;
    else if (__test_opt(kOptConstNegInf, x))
      return gConstNegInf;
    else if (__test_opt(kOptConstNegInf, y))
      return gConstZero;

    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_var_var(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return just_make2(kOptPow, x, "2");
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptDiv, x, y);
  }

  #include "__div_pow.cc"

  static symbol_t __div_log_log(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return just_make2(kOptPow, x, "2");
    return just_make2(kOptDiv, x, y);
  }

  static symbol_t __div_func_func(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return just_make2(kOptPow, x, "2");
    return just_make2(kOptDiv, x, y);
  }

  #include "__polynomial_div.cc"

  static symbol_t __div_sym_mul(const symbol_t &x, const symbol_t &y)
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
    _y = just_make2(kOptDiv, _x, _y);
    play(_y);
    return _y;
    // symbol_t v = create(kOptMul);
    // for (auto it1 = _y.items.begin(); it1 != _y.items.end(); it1++)
    // {
    //   append(v, make(kOptMul, *it1, _x));
    // }
    // return v;
  }

  static symbol_t __div_sym_add(const symbol_t &x, const symbol_t &y)
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

    _y = just_make2(kOptDiv, _x, _y);
    play(_y);
    return _y;
  }

  static symbol_t __div_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return c_pow(x, "2");
    symbol_t z = just_make2(kOptDiv, x, y);
    play(z);
    return z;
  }

  static symbol_t __div_add_add(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return just_make2(kOptPow, x, create_int("2"));
    symbol_t z = just_make2(kOptDiv, x, y);
    play(z);
    return z;
  }

  static symbol_t __div_mul_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = just_make2(kOptMul, x, y);
    play(z);
    return z;
  }

  static symbol_t __div_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    apply_basic_rule(_x);
    return _x;
  }

  symbol_t div(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = execute_cases(kOptDiv, x, y);
    // 整理结果
    sort(z);
    return z;
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

    // 入口
    append_entry(kOptDiv, __div_entry);
  }
} // namespace mysym