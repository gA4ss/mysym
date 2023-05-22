#include <mysym/mysym.h>

namespace mysym
{
  symbol_t fact(const symbol_t &x)
  {
    return default_func_handler(kOptFact, x);
  }
} // namespace mysym