#include <mysym/mysym.h>

namespace mysym
{
  symbol_t abs(const symbol_t &x)
  {
    return default_func_handler(kOptAbs, x);
  }
} // namespace mysym