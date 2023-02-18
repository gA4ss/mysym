#include <mysym/mysym.h>

namespace mysym
{
  list_t complete_sub_expressions(const symbol_t &s)
  {
    list_t l;

    if (is_sym(kind(s)))
    {
      insert(l, s);
      return l;
    }

    // DOING
    // insert(l, s);
    // for (auto it = s.items.begin(); it != s.items.end(); it++)
    // {
    //   insert(l, s);
    // }

    return l;
  }
} // namespace mysym