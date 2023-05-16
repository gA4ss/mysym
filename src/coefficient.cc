#include <mysym/mysym.h>

namespace mysym
{
  int_t coefficient(const symbol_t &s, const symbol_t &x, const int_t &d)
  {
    //
    // 检查参数
    //
    check_param_type(x, kOptVariate);
    check_param_type(d, kOptNumber);

    //
    // 检查s是否是关于x的单项式
    //
    if (is_monomial(s, x))
    {
      int_t k = degree(s, x);
      if (compare(k, d) == 0)
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
      bool diz = compare(d, create_int("0")) == 0 ? true : false;
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
          // 这里修订一个当表达式没有进行自动化简时
          // 对取系数的一个增强。如果自动化简过后
          // 这里一定是全部单项式
          //
          if (is_monomial(*it, x))
          {
            k = degree(*it, x);
            if (compare(k, d) == 0)
              return constant(*it);
          }
          else
          {
            //
            // 这里是非单项式，进行递归
            //
            k = coefficient(*it, x, d);
            if (!is_undefined(k))
              return k;
          }/* end else */
        }/* end else */
      }
    }

    return undefined;
  }

  int_t leading_coefficient(const symbol_t &s, const symbol_t &x)
  {
    return coefficient(s, x, degree(s, x));
  }
} // namespace mysym