#include <mysym/mysym.h>
#include "__test.h"

namespace mysym
{
  /*************************
   *
   * 规则集返回值
   * -1 小于
   * 0 等于
   * 1 大于
   *************************/
  symbol_t cmp(const symbol_t &x, const symbol_t &y);

  /* none值之间的比较
   */
  static symbol_t __cmp_none_xxx(const symbol_t &x, const symbol_t &y)
  {
    return is_none(kind(x)) && is_none(kind(y)) ? gConstZero :
           is_none(kind(x)) && !is_none(kind(y)) ? gConstNegOne : gConstOne;
  }

  /* 常数与符号以及函数的比较
   */
  static symbol_t __cmp_const_xxx(const symbol_t &x, const symbol_t &y)
  {
    return is_const(kind(x)) ? gConstNegOne : gConstOne;
  }

  /* 常数间的比较
   */
  static symbol_t __cmp_const_const(const symbol_t &x, const symbol_t &y)
  {
    mympf::float_t f1;
    mympf::float_t f2;

    //
    // 常数的一些比对
    //
    if (__test_or(is_inf, x, y))
      return is_inf(kind(x)) ? gConstOne : gConstNegOne;
    if (__test_or(is_neg_inf, x, y))
      return is_neg_inf(kind(x)) ? gConstNegOne : gConstOne;
    else if (__test_and_or(is_pi, is_e, x, y))
      return is_pi(kind(x)) ? gConstOne : gConstNegOne;
    else if (__test_and(is_inf, x, y))
      return gConstZero;
    else if (__test_and(is_neg_inf, x, y))
      return gConstZero;
    else if (__test_and(is_e, x, y))
      return gConstZero;
    else if (__test_and(is_pi, x, y))
      return gConstZero;

    //
    // 比较数值
    //
    if ((kind(x) == kOptFrac))
    {
      mympf::float_t n = mympf::create(numerator(x).literal);
      mympf::float_t d = mympf::create(denominator(x).literal);
      f1 = mympf::div(n, d);
    }
    else if (is_num(kind(x)))
    {
      f1 = mympf::create(x.literal);
    }
    else if (is_e(kind(x)))
    {
      f1 = mynum::f::approximate_e();
    }
    else if (is_pi(kind(x)))
    {
      f1 = mynum::f::approximate_pi();
    }

    // precision

    if ((kind(y) == kOptFrac))
    {
      mympf::float_t n = mympf::create(numerator(y).literal);
      mympf::float_t d = mympf::create(denominator(y).literal);
      f2 = mympf::div(n, d);
    }
    else if (is_num(kind(y)))
    {
      f2 = mympf::create(y.literal);
    }
    else if (is_e(kind(y)))
    {
      f2 = mynum::f::approximate_e();
    }
    else if (is_pi(kind(y)))
    {
      f2 = mynum::f::approximate_pi();
    }

    int c = mympf::cmp(f1, f2);
    return c == 0 ? gConstZero : c == 1 ? gConstOne
                                        : gConstNegOne;
  }

  /* 变量与运算符或者函数之间的比较
   */
  static symbol_t __cmp_var_xxx(const symbol_t &x, const symbol_t &y)
  {
    return is_var(kind(x)) ? gConstNegOne : gConstOne;
  }

  /* 两个变量间的比较
   */
  static symbol_t __cmp_var_var(const symbol_t &x, const symbol_t &y)
  {
    return ((x.literal < y.literal) ? gConstNegOne : (x.literal > y.literal) ? gConstOne
                                                                             : gConstZero);
  }

  /* 两个指数函数做比较
   */
  static symbol_t __cmp_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    symbol_t c = cmp(base(x), base(y));
    if (c.literal == "0")
    {
      return cmp(exponent(x), exponent(y));
    }
    return c;
  }

  /* 两个对数函数做比较
   */
  static symbol_t __cmp_log_log(const symbol_t &x, const symbol_t &y)
  {
    symbol_t c = cmp(base(x), base(y));
    if (c.literal == "0")
    {
      return cmp(antilog(x), antilog(y));
    }
    return c;
  }

  /* 两个模函数做比较
   */
  static symbol_t __cmp_mod_mod(const symbol_t &x, const symbol_t &y)
  {
    symbol_t c = cmp(x.items[0], y.items[0]);
    if (c.literal == "0")
    {
      return cmp(x.items[1], y.items[1]);
    }
    return c;
  }

  /* 两个函数做比较
   */
  static symbol_t __cmp_func_func(const symbol_t &x, const symbol_t &y)
  {
    if (kind(x) != kind(y))
    {
      return kind(x) < kind(y) ? gConstNegOne : gConstOne;
    }
    return cmp(base(x), base(y));
  }

  /* 和积与其他的比较
   */
  static symbol_t __cmp_basic_xxx(const symbol_t &x, const symbol_t &y)
  {
    return (is_basic(kind(x))) ? gConstOne : gConstNegOne;
  }

  /* 相同基础运算符作比较
   */
  static symbol_t __cmp_basic(const symbol_t &x, const symbol_t &y)
  {
    //
    // 如果x,y不是相同运算符号
    // 则和大于积
    //
    if (kind(x) != kind(y))
    {
      return (is_add(kind(x))) ? gConstOne : gConstNegOne;
    }

    if (symbol_size(x) < symbol_size(y))
    {
      return gConstNegOne;
    }
    else if (symbol_size(x) > symbol_size(y))
    {
      return gConstOne;
    }

    symbol_t c = gConstZero;
    for (size_t i = 0; i < symbol_size(x); i++)
    {
      c = cmp(x.items[i], y.items[i]);
      if (c.literal != "0")
        return c;
    }
    return gConstZero;
  }

#define check_cmp_number_of_params_number(x)                                 \
  {                                                                          \
    if (symbol_size(x) != 2)                                                 \
    {                                                                        \
      mysym_param_is_out_of_range_exception(                                 \
          "number of compare function params is not equal to 2, n = \'%d\'", \
          symbol_size(x));                                                   \
    }                                                                        \
  }

  static symbol_t __cmp_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    check_cmp_number_of_params_number(_x);
    apply_rule(_x.items[0]);
    apply_rule(_x.items[1]);
    return _x;
  }

  // equ neq lt le gt ge的通用处理函数
#define __order_entry __cmp_entry

  ///////////////////////////////////////////////////
  static symbol_t __equ_xxx_yyy(const symbol_t &x, const symbol_t &y)
  {
    return equ(x, y);
  }

  static symbol_t __neq_xxx_yyy(const symbol_t &x, const symbol_t &y)
  {
    return neq(x, y);
  }

  static symbol_t __lt_xxx_yyy(const symbol_t &x, const symbol_t &y)
  {
    return lt(x, y);
  }

  static symbol_t __le_xxx_yyy(const symbol_t &x, const symbol_t &y)
  {
    return le(x, y);
  }

  static symbol_t __gt_xxx_yyy(const symbol_t &x, const symbol_t &y)
  {
    return gt(x, y);
  }

  static symbol_t __ge_xxx_yyy(const symbol_t &x, const symbol_t &y)
  {
    return ge(x, y);
  }

  //
  // 对比函数
  //
  symbol_t cmp(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptCmp, x, y);
  }

  symbol_t equ(const symbol_t &x, const symbol_t &y)
  {
    return cmp(x, y).literal == "0" ? gConstOne : gConstZero;
  }

  symbol_t neq(const symbol_t &x, const symbol_t &y)
  {
    return cmp(x, y).literal != "0" ? gConstOne : gConstZero;
  }

  symbol_t lt(const symbol_t &x, const symbol_t &y)
  {
    return cmp(x, y).literal == "-1" ? gConstOne : gConstZero;
  }

  symbol_t le(const symbol_t &x, const symbol_t &y)
  {
    symbol_t c = cmp(x, y);
    return (c.literal == "-1") || (c.literal == "0") ? gConstOne : gConstZero;
  }

  symbol_t gt(const symbol_t &x, const symbol_t &y)
  {
    return cmp(x, y).literal == "1" ? gConstOne : gConstZero;
  }

  symbol_t ge(const symbol_t &x, const symbol_t &y)
  {
    symbol_t c = cmp(x, y);
    return (c.literal == "1") || (c.literal == "0") ? gConstOne : gConstZero;
  }

  void register_cmp_rule()
  {
    register_case(kOptCmp, make_optsign_any(kOptNone), __cmp_none_xxx);
    register_case(kOptCmp, make_optsign_exclude("const"), __cmp_const_xxx);
    register_case(kOptCmp, make_optsign("const", "const"), __cmp_const_const);
    register_case(kOptCmp, make_optsign_any(kOptVariate), __cmp_var_xxx);
    register_case(kOptCmp, make_optsign(kOptVariate, kOptVariate), __cmp_var_var);
    register_case(kOptCmp, make_optsign(kOptPow, kOptPow), __cmp_pow_pow);
    register_case(kOptCmp, make_optsign(kOptLog, kOptLog), __cmp_log_log);
    register_case(kOptCmp, make_optsign(kOptMod, kOptMod), __cmp_mod_mod);
    register_case(kOptCmp, make_optsign("func", "func"), __cmp_func_func);
    register_case(kOptCmp, make_optsign_exclude("basic"), __cmp_basic_xxx);
    register_case(kOptCmp, make_optsign("basic", "basic"), __cmp_basic);
    append_entry(kOptCmp, __cmp_entry);
    // ----------------------------------------
    append_entry(kOptEqu, __order_entry);
    append_entry(kOptNotEqu, __order_entry);
    append_entry(kOptLT, __order_entry);
    append_entry(kOptLE, __order_entry);
    append_entry(kOptGT, __order_entry);
    append_entry(kOptGE, __order_entry);
    // ----------------------------------------
    register_case(kOptEqu, make_optsign("all", "all"), __equ_xxx_yyy);
    register_case(kOptNotEqu, make_optsign("all", "all"), __neq_xxx_yyy);
    register_case(kOptLT, make_optsign("all", "all"), __lt_xxx_yyy);
    register_case(kOptLE, make_optsign("all", "all"), __le_xxx_yyy);
    register_case(kOptGT, make_optsign("all", "all"), __gt_xxx_yyy);
    register_case(kOptGE, make_optsign("all", "all"), __ge_xxx_yyy);
  }
} // namespace mysym