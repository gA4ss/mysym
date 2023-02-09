#include <mysym/mysym.h>

namespace mysym
{
  symbol_t operand(const symbol_t &s, size_t i)
  {
    if (i >= symbol_size(s))
    {
      mysym_param_is_out_of_range_exception("i = %lu", i);
    }
    return s.items[i];
  }
} // namespace mysym