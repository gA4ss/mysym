#include <mysym/mysym.h>

namespace mysym
{

  symbol_t operator_frame(const symbol_t &x, const symbol_t &y, fptr_operator_frame_t fopt)
  {
    symbol_t z;

    if (is_single(x) && is_single(y))
    {
      z = fopt(x, y);
    }
    else if ((is_single(x) && !is_single(y)) ||
             (!is_single(x) && is_single(y)))
    {
    }
    else
    {
    }

    return z;
  }
} // namespace mysym