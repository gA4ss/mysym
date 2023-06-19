#include <mysym/mysym.h>

namespace mysym
{
  symbol_t log_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    for (auto it = _x.items.begin(); it != _x.items.end(); it++)
    {
      apply_rule(*it);
    }
    return _x;
  }

  symbol_t log(const symbol_t &x, const symbol_t &y)
  {
    return default_func_handler(kOptLog, x, y);
  }
} // namespace mysym