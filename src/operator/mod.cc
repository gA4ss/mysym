#include <mysym/mysym.h>

namespace mysym
{
  symbol_t mod(const symbol_t &x, const symbol_t &y)
  {
    return default_func_handler(kOptMod, x, y);
  }
} // namespace mysym