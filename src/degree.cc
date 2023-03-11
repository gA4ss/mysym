#include <mysym/mysym.h>

namespace mysym
{
  static int_t __degree_monomial(const symbol_t &s, const list_t &xs)
  {
    if (is_const(kind(s)))
      return gConstZero;

    if (is_var(kind(s)))
    {
      if (find(xs, s))
        return gConstOne;
      else
        return gConstZero;
    }

    if (is_pow(kind(s)))
    {
      symbol_t b = base(s);
      symbol_t p = exponent(s);
      if (find(xs, b) && is_int(kind(p)))
        return p;
      return gConstZero;
    }

    if (is_mul(kind(s)))
    {
      int_t d = gConstZero;
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
        if (is_const(kind(*it)))
          continue;

        if (is_var(kind(*it)))
        {
          //
          // 这里假设每个变量在单项式中仅出现一次，已经经过了合并。
          //
          if (find(xs, *it))
          {
            d = add(d, gConstOne);
          }
        }
        else if (is_pow(kind(*it)))
        {
          symbol_t b = base(*it);
          symbol_t p = exponent(*it);
          if ((find(xs, b)) && (is_int(kind(p))))
          {
            d = add(d, p);
          }
        }
      }
      return d;
    }
    return undefined;
  }

  int_t degree(const symbol_t &s, const symbol_t &x)
  {
    // 检查参数
    check_param_type(x, kOptVariate);

    int_t d = gConstUDF;
    if (is_add(kind(s)))
    {
      for (size_t i = 0; i < number_of_operands(s); i++)
      {
        int_t k = __degree_monomial(operand(s, i), {x});
        if (is_und(kind(k)))
          continue;
        else
        {
          if (cmp(d, k) < 0)
            d = k;
        }
      }
      return d;
    }

    //
    // 剩单项式了
    //
    return __degree_monomial(s, {x});
  }

  int_t degree(const symbol_t &s, const list_t &xs)
  {
    check_list_all_variate_type(xs);

    int_t d = gConstUDF;
    if (is_add(kind(s)))
    {
      for (size_t i = 0; i < number_of_operands(s); i++)
      {
        int_t k = __degree_monomial(operand(s, i), xs);
        if (is_und(kind(k)))
          continue;
        else
        {
          if (cmp(d, k) < 0)
            d = k;
        }
      }
      return d;
    }

    //
    // 剩单项式了
    //
    return __degree_monomial(s, xs);
  }
} // namespace mysym