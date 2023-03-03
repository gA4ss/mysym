#include <mysym/mysym.h>

namespace mysym
{
  static int_t degree_monomial(const symbol_t &s, const symbol_t &x)
  {
    if (is_const(kind(s)))
      return create_int("0");
    else if (cmp(s, x) == 0)
      return create_int("1");
    else if (is_pow(kind(s)))
    {
      symbol_t b = base(s);
      symbol_t ep = exponent(s);
      if ((cmp(b, x) == 0) && (is_int(kind(ep))))
        return ep;
    }
    else if (is_mul(kind(s)))
    {
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
      }
    }
    return undefined;
  }

  int_t degree(const symbol_t &s, const symbol_t &x)
  {
    int_t d = degree_monomial(s, x);
    if (!is_und(kind(d)))
      return d;
    else if (is_add(kind(s)))
    {
      d = create_int("0");
      for (size_t i = 0; i < number_of_operands(s); i++)
      {
        int_t k = degree_monomial(operand(s, i), x);
        //
        // 这里如果是单项式返回无定义就退出，太生硬了。
        // 如果是无定义，则进行下一项。忽略无定义。
        //
        // if (is_und(kind(k)))
        //   return undefined;
        // else
        if (!is_und(kind(k)))
        {
          if (cmp(d, k) < 0)
            d = k;
        }
      }
      return d;
    }
    return undefined;
  }
} // namespace mysym