#include <mysym/mysym.h>
#include "__test.h"

namespace mysym
{
  static inline symbol_t __mympf_to_symbol(const mympf::float_t &f)
  {
    return create_flt(mympf::print_string(f));
  }

  static inline symbol_t __mympf_fraction_to_symbol(const mynum::fraction_t &f)
  {
    return c_frac(mympz::print_string(f.first), mympz::print_string(f.second));
  }

  static symbol_t __add_num_num(const symbol_t &x, const symbol_t &y)
  {
    mympf::float_t f1 = mympf::create(x.literal);
    mympf::float_t f2 = mympf::create(y.literal);
    return __mympf_to_symbol(mympf::add(f1, f2));
  }

  static symbol_t __add_num_frac(const symbol_t &x, const symbol_t &y)
  {
    mympf::float_t f1, f2;
    if (is_frac(kind(x)))
    {
      f1 = mympf::create(frac_to_num(x).literal);
      f2 = mympf::create(y.literal);
    }
    else
    {
      f1 = mympf::create(frac_to_num(y).literal);
      f2 = mympf::create(x.literal);
    }
    return __mympf_to_symbol(mympf::add(f1, f2));
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
    // mympf::float_t v1 = mympf::create(x.literal), v2 = mympf::create(y.literal);
    // mynum::fraction_t f1 = mynum::f::fraction(v1), f2 = mynum::f::fraction(v2);
    mynum::fraction_t f1 = {mympz::create(numerator(x).literal), mympz::create(denominator(x).literal)};
    mynum::fraction_t f2 = {mympz::create(numerator(y).literal), mympz::create(denominator(y).literal)};
    mynum::fraction_t f3 = mynum::f::add(f1, f2);
    return __mympf_fraction_to_symbol(f3);
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
    if (compare(x, y) == 0)
    {
      if (is_inf(kind(x)))
        return gConstInf;
      else if (is_neg_inf(kind(x)))
        return gConstNegInf;
      else
        return just_make2(kOptMul, "2", x);
    }

    if (__test_and_or(is_inf, is_neg_inf, x, y))
      return gConstZero;
    else if (__test_or(is_inf, x, y))
      return gConstInf;
    else if (__test_or(is_neg_inf, x, y))
      return gConstNegInf;

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
    if (compare(x, y) == 0)
      return just_make2(kOptMul, "2", x);
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_func_func(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return just_make2(kOptMul, "2", x);
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __add_sym_mul(const symbol_t &x, const symbol_t &y)
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

    // list_t vars = variables(_y);
    // if (size(vars) != 1)
    // {
    //   return just_make2(kOptAdd, x, y);
    // }
    // else if (compare(_x, vars[0]) == 0)
    // {
    //   // 可以相加
    //   symbol_t a = __add_num_num(gConstOne, constant(_y));
    //   return just_make2(kOptMul, a, _x);
    // }
    return just_make2(kOptAdd, _x, _y);
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
    apply_basic_rule(_y);
    return _y;
  }

#if 0
  static bool __c_add_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return __test_and(is_mul, x, y);
  }
  static symbol_t __e_add_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  static bool __c_add_add_add(const symbol_t &x, const symbol_t &y)
  {
    return __test_and(is_add, x, y);
  }
  static symbol_t __e_add_add_add(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  static bool __c_add_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return __test_and_or(is_add, is_mul, x, y);
  }
  static symbol_t __e_add_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }
#endif

  static symbol_t __add_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    apply_basic_rule(_x);
    return _x;
  }

  symbol_t add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = execute_cases(kOptAdd, x, y);
    //
    // 交换律对加法后的结果进行排序
    //
    apply_commutative_law(z);
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

    // 函数 + xxx
    register_case(kOptAdd, make_optsign("func", "func"), __add_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptAdd, make_optsign("sym", kOptMul), __add_sym_mul);
    register_case(kOptAdd, make_optsign("sym", kOptAdd), __add_sym_add);

#if 0
    // 多项式 与 单项式
    register_case(kOptAdd, __c_add_mul_mul, __e_add_mul_mul);
    register_case(kOptAdd, __c_add_add_add, __e_add_add_add);
    register_case(kOptAdd, __c_add_mul_add, __e_add_mul_add);
#endif
    // 入口
    append_entry(kOptAdd, __add_entry);
  }
} // namespace mysym