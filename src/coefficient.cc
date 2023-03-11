#include <mysym/mysym.h>

namespace mysym
{
  int_t coefficient(const symbol_t &s, const symbol_t &x, const int_t &d)
  {
    //
    // 检查参数
    //
    check_param_type(x, kOptVariate);
    check_param_type(d, kOptInteger);

    //
    // 检查s是否是关于x的单项式
    //
    if (is_monomial(s, x))
    {
      int_t k = degree(s, x);
      if (cmp(k, d) == 0)
        return constant(s);
      else
        return undefined;
    }

    //
    // 如果不是，则是一个多项式。
    //
    if (is_add(kind(s)))
    {
      int_t k = create_none();
      bool diz = cmp(d, create_int("0")) == 0 ? true : false;
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
        //
        // 如果d为0，则找寻常数
        //
        if (diz)
        {
          if (is_const(kind(*it)))
            return *it;
        }
        else
        {
          //
          // 非x的单项式则跳过
          //
          if (!is_monomial(*it, x))
            continue;

          k = degree(*it, x);
          if (cmp(k, d) == 0)
            return constant(*it);
        }
      }
    }

    return undefined;
  }

  int_t leading_coefficient(const symbol_t &s, const symbol_t &x)
  {
    return coefficient(s, x, degree(s, x));
  }
} // namespace mysym