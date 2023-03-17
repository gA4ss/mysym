#include <mysym/mysym.h>

namespace mysym
{
  //   symbol_t nature_add_nature(const symbol_t &x, const symbol_t &y)
  //   {
  //     symbol_t z;

  //     if (cmp(x, y) == 0)
  //     {
  //       if (is_inf(kind(x)))
  //       {
  //         z = gConstInf;
  //       }
  //       else if (is_neg_inf(kind(x)))
  //       {
  //         z = gConstNegInf;
  //       }
  //       else // x = y = e
  //       {
  //         z = c_mul("2", x);
  //       }
  //     }
  //     else
  //     {
  //       if ((is_inf(kind(x)) && (is_neg_inf(kind(y)))) ||
  //           (is_neg_inf(kind(x)) && (is_inf(kind(y)))))
  //       {
  //         z = gConstZero;
  //       }
  //       else
  //       {
  //         if (is_inf(kind(x)) || is_inf(kind(y)))
  //         {
  //           z = gConstInf;
  //         }
  //         else if (is_neg_inf(kind(x)) || (is_neg_inf(kind(y))))
  //         {
  //           z = gConstNegInf;
  //         }
  //       }
  //     }
  //     return z;
  //   }

  //   symbol_t nature_add_frac_num(const symbol_t &x, const symbol_t &y)
  //   {
  //     symbol_t z;
  //     if (is_inf(kind(x)) || is_inf(kind(y)))
  //     {
  //       z = gConstInf;
  //     }
  //     else if (is_neg_inf(kind(x)) || is_neg_inf(kind(y)))
  //     {
  //       z = gConstNegInf;
  //     }
  //     else
  //     {
  //       z = c_add(x, y);
  //     }
  //     return z;
  //   }

  // #define __not_nature(o) (is_num(o) || is_frac(o))
  //   static symbol_t __const_add_const(const symbol_t &x, const symbol_t &y)
  //   {
  //     symbol_t z;

  //     if (is_num(kind(x)) && is_num(kind(y)))
  //     {
  //       z = __num_add_num(x, y);
  //     }
  //     else if (is_frac(kind(x)) && is_frac(kind(y)))
  //     {
  //       z = __frac_add_frac(x, y);
  //     }
  //     else if ((is_frac(kind(x)) && is_num(kind(y))) ||
  //              (is_num(kind(x)) && is_frac(kind(y))))
  //     {
  //       z = __num_add_frac(x, y);
  //     }
  //     else if (is_nature(kind(x)) && is_nature(kind(y)))
  //     {
  //       z = __nature_add_nature(x, y);
  //     }
  //     else if ((is_nature(kind(x)) && __not_nature(kind(y))) ||
  //              (__not_nature(kind(x)) && is_nature(kind(y))))
  //     {
  //       z = __nature_add_frac_num(x, y);
  //     }
  //     else
  //     {
  //     }
  //     return z;
  //   }

  //   static symbol_t __var_add_var(const symbol_t &x, const symbol_t &y)
  //   {
  //     symbol_t z;
  //     return z;
  //   }

  //   static symbol_t __const_add_var(const symbol_t &x, const symbol_t &y)
  //   {
  //     symbol_t z;
  //     return z;
  //   }

  //   static symbol_t __func_add_func(const symbol_t &x, const symbol_t &y)
  //   {
  //     symbol_t z;
  //     return z;
  //   }

  //   static symbol_t __add(const symbol_t &x, const symbol_t &y)
  //   {
  //     symbol_t z;
  //     if (is_const(kind(x)) && is_const(kind(y)))
  //     {
  //       z = __const_add_const(x, y);
  //     }
  //     else if (is_var(kind(x)) && is_var(kind(y)))
  //     {
  //       z = __var_add_var(x, y);
  //     }
  //     else if (is_func(kind(x)) && is_func(kind(y)))
  //     {
  //       z = __func_add_func(x, y);
  //     }
  //     else if ((is_const(kind(x)) && is_var(kind(y))) ||
  //              (is_var(kind(x)) && is_const(kind(y))))
  //     {
  //       z = __const_add_var(x, y);
  //     }
  //     else
  //     {
  //       // 这里是单个变量与函数、单项式或者多项式
  //     }

  //     return z;
  //   }

  bool __c_add_num_num(const symbol_t &x, const symbol_t &y)
  {
    return is_num(kind(x)) && is_num(kind(y));
  }
  symbol_t __e_add_num_num(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return ((is_num(kind(x)) && is_frac(kind(y))) ||
            (is_num(kind(y)) && is_frac(kind(x))));
  }
  symbol_t __e_add_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_num_var(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_num_var(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_num_func(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_num_func(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_var_var(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_var_var(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_var_func(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_var_func(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_func_func(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add_func_func(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add(const symbol_t &x, const symbol_t &y)
  {
    return false;
  }
  symbol_t __e_add(const symbol_t &x, const symbol_t &y)
  {
    return undefined;
  }

  bool __c_add_entry(const symbol_t &x)
  {
    return false;
  }
  symbol_t __e_add_entry(const symbol_t &x)
  {
    return undefined;
  }

  symbol_t add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    return z;
  }
} // namespace mysym