#include <mysym/mysym.h>

namespace mysym
{
  list_t variables(const symbol_t &s)
  {
    list_t l;
    if (is_single(s))
    {
      append(l, s);
    }
    else
    {
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
      }
    }
    return l;
  }

  list_t constants(const symbol_t &s)
  {
    list_t l;
    return l;
  }

  list_t integers(const symbol_t &s)
  {
    list_t l;
    return l;
  }

  list_t reals(const symbol_t &s)
  {
    list_t l;
    return l;
  }
} // namespace mysym