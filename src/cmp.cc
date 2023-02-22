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
    if ((is_const(kind(s1))) && (!is_const(kind(s2))))
      return -1;
    // else if ((!is_const(kind(s1))) && (is_const(kind(s2))))
    //   return 1;
    return 1;
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

  /* 函数与变量间的比较
   */
  static bool __rule_2(const symbol_t &s1, const symbol_t &s2)
  {
    return (
        ((is_var(kind(s1))) && (is_func(kind(s2)))) ||
        ((is_func(kind(s1))) && (is_var(kind(s2)))));
  }
  static int __cmp_2(const symbol_t &s1, const symbol_t &s2)
  {
    if ((is_var(kind(s1))) && (is_func(kind(s2))))
      return -1;
    // else if ((is_func(kind(s1))) && (is_var(kind(s2))))
    //   return 1;
    return 1;
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

  typedef bool (*fptr_cmp_condition_t)(const symbol_t &, const symbol_t &);
  typedef int (*fptr_cmp_do_t)(const symbol_t &, const symbol_t &);
  typedef std::vector<std::pair<fptr_cmp_condition_t, fptr_cmp_do_t>> cmp_rule_table_t;

  static cmp_rule_table_t __cmp_rule_table = {
      {__rule_0, __cmp_0},
      {__rule_1, __cmp_1},
      {__rule_2, __cmp_2},
      {__rule_3, __cmp_3}
  };

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