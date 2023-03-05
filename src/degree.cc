#include <mysym/mysym.h>

namespace mysym
{
  static int_t degree_monomial(const symbol_t &s, const symbol_t &x)
  {
    // 检查参数
    if (!is_var(kind(x)))
    {
      mysym_invalid_param_type_exception("it's must be variate type, it's %d.", kind(x));
    }

    if (is_const(kind(s)))
      return create_int("0");

    if (cmp(s, x) == 0)
    {
      return create_int("1");
    }
    else if (is_pow(kind(s)))
    {
      symbol_t b = base(s);
      symbol_t ep = exponent(s);
      if ((cmp(b, x) == 0) && (is_int(kind(ep))))
        return ep;
    }
    else if (is_mul(kind(s)))
    {
      int_t d = create_none();
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
        int_t k = degree_monomial(*it, x);
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
    return undefined;
  }

  int_t degree(const symbol_t &s, const symbol_t &x)
  {
    // 检查参数
    if (!is_var(kind(x)))
    {
      mysym_invalid_param_type_exception("it's must be variate type, it's %d.", kind(x));
    }

    int_t d;
    if (is_add(kind(s)))
    {
      d = create_none();
      for (size_t i = 0; i < number_of_operands(s); i++)
      {
        int_t k = degree_monomial(operand(s, i), x);
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
    d = degree_monomial(s, x);
    return d;
  }

  int_t degree(const symbol_t &s, const list_t &xs)
  {
    return undefined;
  }
} // namespace mysym