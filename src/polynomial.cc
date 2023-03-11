#include <mysym/mysym.h>

namespace mysym
{
  bool is_polynomial(const symbol_t &s, const symbol_t &x)
  {
    //
    // 检查参数
    //
    if (!is_var(kind(x)))
    {
      mysym_invalid_param_type_exception("it's must be variate type, it's %d.", kind(x));
    }

    if (is_monomial(s, x))
      return true;

    if (kind(s) == kOptAdd)
    {
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
        if (!is_monomial(*it, x))
          return false;
      }
      return true;
    }

    return false;
  }

  bool is_polynomial(const symbol_t &s, const list_t &xs)
  {
    for (auto it = xs.begin(); it != xs.end(); it++)
    {
      if (is_polynomial(s, *it) == true)
        return true;
    }
    return false;
  }
} // namespace mysym