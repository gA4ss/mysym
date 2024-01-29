#include <mysym/mysym.h>
#include <mysym/set.hpp>
#include "__misc.h"

namespace mysym
{
  symbol_t inverse_add(const symbol_t &x)
  {
    return opposite(x);
  }

  symbol_t inverse_mul(const symbol_t &x)
  {
    return pow(x, gConstNegInf);
  }
} // namespace mysym