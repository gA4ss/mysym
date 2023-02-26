#include <mysym/mysym.h>

namespace mysym
{
  /*************************
   * 比较顺序：
   * 1. 函数与符号、函数的比较
   * 2.
   *
   * 规则集返回值
   * -1 小于
   * 0 等于
   * 1 大于
   *************************/
  int cmp(const symbol_t &s1, const symbol_t &s2);

  /* 常数与符号以及函数的比较
   */
  static bool __rule_0(const symbol_t &s1, const symbol_t &s2)
  {
    return (
        ((is_const(kind(s1))) && (!is_const(kind(s2)))) ||
        ((!is_const(kind(s1))) && (is_const(kind(s2)))));
  }
  static int __cmp_0(const symbol_t &s1, const symbol_t &s2)
  {
    // if ((is_const(kind(s1))) && (!is_const(kind(s2))))
    //   return -1;
    // else if ((!is_const(kind(s1))) && (is_const(kind(s2))))
    //   return 1;
    // return 1;
    return is_const(kind(s1)) ? -1 : 1;
  }

  /* 常数间的比较
   */
  static bool __rule_1(const symbol_t &s1, const symbol_t &s2)
  {
    return ((is_const(kind(s1))) && (is_const(kind(s2))));
  }
  static int __cmp_1(const symbol_t &s1, const symbol_t &s2)
  {
    mympf::float_t f1;
    mympf::float_t f2;

    if ((kind(s1) == kOptFrac))
    {
      mympf::float_t n = mympf::create(numerator(s1).literal);
      mympf::float_t d = mympf::create(denominator(s1).literal);
      f1 = mympf::div(n, d);
    }
    else if (is_num(kind(s1)))
    {
      f1 = mympf::create(s1.literal);
    }

    if ((kind(s2) == kOptFrac))
    {
      mympf::float_t n = mympf::create(numerator(s2).literal);
      mympf::float_t d = mympf::create(denominator(s2).literal);
      f2 = mympf::div(n, d);
    }
    else if (is_num(kind(s2)))
    {
      f2 = mympf::create(s2.literal);
    }

    return mympf::cmp(f1, f2);
  }

  /* 变量与运算符或者函数之间的比较
   */
  static bool __rule_2(const symbol_t &s1, const symbol_t &s2)
  {
    return ((is_var(kind(s1))) && (!is_var(kind(s2)))) ||
           ((!is_var(kind(s1))) && (is_var(kind(s2))));
  }
  static int __cmp_2(const symbol_t &s1, const symbol_t &s2)
  {
    // if ((is_var(kind(s1))) && (is_func(kind(s2))))
    //   return -1;
    // else if ((is_func(kind(s1))) && (is_var(kind(s2))))
    //   return 1;
    // return 1;
    return is_var(kind(s1)) ? -1 : 1;
  }

  /* 两个变量间的比较
   */
  static bool __rule_3(const symbol_t &s1, const symbol_t &s2)
  {
    return ((is_var(kind(s1))) && (is_var(kind(s2))));
  }
  static int __cmp_3(const symbol_t &s1, const symbol_t &s2)
  {
    return (
        (s1.literal < s2.literal) ? -1 : (s1.literal > s2.literal) ? 1
                                                                   : 0);
  }

  /* 两个指数函数做比较
   */
  static bool __rule_4(const symbol_t &s1, const symbol_t &s2)
  {
    return ((is_pow(kind(s1))) && (is_pow(kind(s2))));
  }
  static int __cmp_4(const symbol_t &s1, const symbol_t &s2)
  {
    int c = cmp(base(s1), base(s2));
    if (c == 0)
    {
      return cmp(exponent(s1), exponent(s2));
    }
    return c;
  }

  /* 两个对数函数做比较
   */
  static bool __rule_5(const symbol_t &s1, const symbol_t &s2)
  {
    return (is_log(kind(s1))) && (is_log(kind(s2)));
  }
  static int __cmp_5(const symbol_t &s1, const symbol_t &s2)
  {
    int c = cmp(base(s1), base(s2));
    if (c == 0)
    {
      return cmp(antilog(s1), antilog(s2));
    }
    return c;
  }

  /* 两个模函数做比较
   */
  static bool __rule_6(const symbol_t &s1, const symbol_t &s2)
  {
    return (is_mod(kind(s1))) && (is_mod(kind(s2)));
  }
  static int __cmp_6(const symbol_t &s1, const symbol_t &s2)
  {
    int c = cmp(s1.items[0], s2.items[0]);
    if (c == 0)
    {
      return cmp(s1.items[1], s2.items[1]);
    }
    return c;
  }

  /* 两个函数做比较
   */
  static bool __rule_7(const symbol_t &s1, const symbol_t &s2)
  {
    return (is_func(kind(s1))) && (is_func(kind(s2)));
  }
  static int __cmp_7(const symbol_t &s1, const symbol_t &s2)
  {
    if (kind(s1) != kind(s2))
    {
      return kind(s1) < kind(s2) ? -1 : 1;
    }

    return cmp(base(s1), base(s2));
  }

  /* 和与积作比较，和大于积
   */
  static bool __rule_8(const symbol_t &s1, const symbol_t &s2)
  {
    return (is_add(kind(s1)) && is_mul(kind(s2))) ||
           (is_mul(kind(s1)) && is_add(kind(s2)));
  }
  static int __cmp_8(const symbol_t &s1, const symbol_t &s2)
  {
    return (is_add(kind(s1))) ? 1 : -1;
  }

  /* 相同基础运算符作比较
   */
  static bool __rule_9(const symbol_t &s1, const symbol_t &s2)
  {
    return (is_add(kind(s1)) && (is_add(kind(s2)))) ||
           (is_mul(kind(s1)) && (is_mul(kind(s2))));
  }
  static int __cmp_9(const symbol_t &s1, const symbol_t &s2)
  {
    if (symbol_size(s1) < symbol_size(s2))
    {
      return -1;
    }
    else if (symbol_size(s1) > symbol_size(s2))
    {
      return 1;
    }

    int c = 0;
    for (size_t i = 0; i < symbol_size(s1); i++)
    {
      c = cmp(s1.items[i], s2.items[i]);
      if (c != 0)
        return c;
    }
    return 0;
  }

  /* 和运算符与函数间的比较
   */
  static bool __rule_10(const symbol_t &s1, const symbol_t &s2)
  {
    return (is_add(kind(s1)) && is_func(kind(s2))) ||
           (is_func(kind(s1)) && is_add(kind(s2)));
  }
  static int __cmp_10(const symbol_t &s1, const symbol_t &s2)
  {
    return (is_add(kind(s1))) ? 1 : -1;
  }

  /* 积运算符与函数间的比较
   */
  static bool __rule_11(const symbol_t &s1, const symbol_t &s2)
  {
    return (is_mul(kind(s1)) && is_func(kind(s2))) ||
           (is_func(kind(s1)) && is_mul(kind(s2)));
  }
  static int __cmp_11(const symbol_t &s1, const symbol_t &s2)
  {
    return (is_mul(kind(s1))) ? -1 : 1;
  }

  typedef bool (*fptr_cmp_condition_t)(const symbol_t &, const symbol_t &);
  typedef int (*fptr_cmp_do_t)(const symbol_t &, const symbol_t &);
  typedef std::vector<std::pair<fptr_cmp_condition_t, fptr_cmp_do_t>> cmp_rule_table_t;

  static cmp_rule_table_t __cmp_rule_table = {
      {__rule_0, __cmp_0},
      {__rule_1, __cmp_1},
      {__rule_2, __cmp_2},
      {__rule_3, __cmp_3},
      {__rule_4, __cmp_4},
      {__rule_5, __cmp_5},
      {__rule_6, __cmp_6},
      {__rule_7, __cmp_7},
      {__rule_8, __cmp_8},
      {__rule_9, __cmp_9},
      {__rule_10, __cmp_10},
      {__rule_11, __cmp_11}};

  int cmp(const symbol_t &s1, const symbol_t &s2)
  {
    for (auto rule : __cmp_rule_table)
    {
      if (rule.first(s1, s2))
        return rule.second(s1, s2);
    }

    mysym_exception("[s1 = %d, s2 = %d] not found compare rule.", kind(s1), kind(s2));
  }
} // namespace mysym