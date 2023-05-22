#include <mysym/mysym.h>

namespace mysym
{
  symbol_t pow(const symbol_t &x, const symbol_t &y)
  {
    return default_func_handler(kOptPow, x, y);
  }
} // namespace mysym