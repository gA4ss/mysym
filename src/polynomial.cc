#include <mysym/mysym.h>

namespace mysym
{
  bool is_polynomial(const symbol_t &s, const symbol_t &x)
  {
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
} // namespace mysym