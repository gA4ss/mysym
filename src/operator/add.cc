#include <mysym/mysym.h>

namespace mysym
{
  static symbol_t __num_add_num(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    return z;
  }

  static symbol_t __frac_add_frac(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    return z;
  }

  static symbol_t __num_add_frac(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    return z;
  }

  static symbol_t __nature_add_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (cmp(x, y) == 0)
    {
      if (is_inf(kind(x)))
      {
        z = gConstInf;
      }
      else if (is_neg_inf(kind(x)))
      {
        z = gConstNegInf;
      }
      else // x = y = e
      {
        z = c_mul("2", x);
      }
    }
    else
    {
      if ((is_inf(kind(x)) && (is_neg_inf(kind(y)))) ||
          (is_neg_inf(kind(x)) && (is_inf(kind(y)))))
      {
        z = gConstZero;
      }
      else
      {
        if (is_inf(kind(x)) || is_inf(kind(y)))
        {
          z = gConstInf;
        }
        else if (is_neg_inf(kind(x)) || (is_neg_inf(kind(y))))
        {
          z = gConstNegInf;
        }
      }
    }
    return z;
  }

  static symbol_t __nature_add_frac_num(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (is_inf(kind(x)) || is_inf(kind(y)))
    {
      z = gConstInf;
    }
    else if (is_neg_inf(kind(x)) || is_neg_inf(kind(y)))
    {
      z = gConstNegInf;
    }
    else
    {
      z = c_add(x, y);
    }
    return z;
  }

#define __not_nature(o) (is_num(o) || is_frac(o))
  static symbol_t __const_add_const(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (is_num(kind(x)) && is_num(kind(y)))
    {
      z = __num_add_num(x, y);
    }
    else if (is_frac(kind(x)) && is_frac(kind(y)))
    {
      z = __frac_add_frac(x, y);
    }
    else if ((is_frac(kind(x)) && is_num(kind(y))) ||
             (is_num(kind(x)) && is_frac(kind(y))))
    {
      z = __num_add_frac(x, y);
    }
    else if (is_nature(kind(x)) && is_nature(kind(y)))
    {
      z = __nature_add_nature(x, y);
    }
    else if ((is_nature(kind(x)) && __not_nature(kind(y))) ||
             (__not_nature(kind(x)) && is_nature(kind(y))))
    {
      z = __nature_add_frac_num(x, y);
    }
    else
    {
    }
    return z;
  }

  static symbol_t __var_add_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    return z;
  }

  static symbol_t __const_add_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    return z;
  }

  static symbol_t __func_add_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    return z;
  }

  static symbol_t __add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (is_const(kind(x)) && is_const(kind(y)))
    {
      z = __const_add_const(x, y);
    }
    else if (is_var(kind(x)) && is_var(kind(y)))
    {
      z = __var_add_var(x, y);
    }
    else if (is_func(kind(x)) && is_func(kind(y)))
    {
      z = __func_add_func(x, y);
    }
    else if ((is_const(kind(x)) && is_var(kind(y))) ||
             (is_var(kind(x)) && is_const(kind(y))))
    {
      z = __const_add_var(x, y);
    }
    else
    {
      // 这里是单个变量与函数、单项式或者多项式
    }

    return z;
  }

  symbol_t add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = operator_frame(x, y, __add);
    return z;
  }

  symbol_t simplify_sum(const symbol_t &s)
  {
    return s;
  }
} // namespace mysym