#include <mysym/mysym.h>

namespace mysym
{
  int compare(const symbol_t &s1, const symbol_t &s2)
  {
    symbol_t c = cmp(s1, s2);
    return c.literal == "0" ? 0 : c.literal == "1" ? 1
                                                   : -1;
  }
} // namespace mysym