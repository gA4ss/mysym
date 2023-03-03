#include <mysym/mysym.h>

namespace mysym
{
  void copy(const symbol_t &s, symbol_t &d)
  {
    d.opt = s.opt;
    d.literal = s.literal;
    d.items = s.items;
  }
} // namespace mysym