#include <mysym/mysym.h>

namespace mysym
{
  symbol_t log(const symbol_t &x, const symbol_t &y)
  {
    return default_func_handler(kOptLog, x, y);
  }
} // namespace mysym