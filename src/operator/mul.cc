#include <mysym/mysym.h>
#include "__test.h"

namespace mysym
{
  static inline symbol_t __mympf_to_symbol(const mympf::float_t &f)
  {
    return create_flt(mympf::print_string(f));
  }

  static symbol_t __mul_num_num(const symbol_t &x, const symbol_t &y)
  {
    mympf::float_t f1 = mympf::create(x.literal);
    mympf::float_t f2 = mympf::create(y.literal);
    return __mympf_to_symbol(mympf::mul(f1, f2));
  }

  static symbol_t __mul_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return compute_frac_num(kOptMul, x, y);
  }

  static symbol_t __mul_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_num_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return compute_frac_frac(kOptMul, x, y);
  }

  static symbol_t __mul_frac_nature(const symbol_t &x, const symbol_t &y)
  {
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

    if (__test_and_or(is_inf, is_neg_inf, x, y))
      return gConstNegInf;
    else if (__test_or(is_inf, x, y))
      return gConstInf;
    else if (__test_or(is_neg_inf, x, y))
      return gConstNegInf;

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
    apply_basic_rule(_y);
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
    apply_basic_rule(_y);
    return _y;
  }

#if 0
  static symbol_t __mul_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return make(kOptMul, create_int("2"), x);
    return just_make2(kOptAdd, x, y);
  }

  static symbol_t __mul_add_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = c_add(x, y);
    combine_like_terms(z);
    return z;
  }

  static symbol_t __mul_mul_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = c_add(x, y);
    apply_rule(z);
    return z;
  }
#endif

  static symbol_t __mul_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    apply_basic_rule(_x);
    return _x;
  }

  symbol_t mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = execute_cases(kOptMul, x, y);
    //
    // 交换律对加法后的结果进行排序
    //
    apply_commutative_law(z);
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

    // 函数 + xxx
    register_case(kOptMul, make_optsign("func", "func"), __mul_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptMul, make_optsign("sym", kOptMul), __mul_sym_mul);
    register_case(kOptMul, make_optsign("sym", kOptAdd), __mul_sym_add);

#if 0
    // 多项式 与 单项式
    register_case(kOptMul, make_optsign(kOptMul, kOptMul), __mul_mul_mul);
    register_case(kOptMul, make_optsign(kOptAdd, kOptAdd), __mul_add_add);
    register_case(kOptMul, make_optsign(kOptMul, kOptAdd), __mul_mul_add);
#endif
    // 入口
    append_entry(kOptMul, __mul_entry);
  }
} // namespace mysym