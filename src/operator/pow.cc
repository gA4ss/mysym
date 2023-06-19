#include <mysym/mysym.h>

namespace mysym
{
  symbol_t pow_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    for (auto it = _x.items.begin(); it != _x.items.end(); it++)
    {
      apply_rule(*it);
    }
    return _x;
  }

  symbol_t pow(const symbol_t &x, const symbol_t &y)
  {
    return default_func_handler(kOptPow, x, y);
  }
} // namespace mysym