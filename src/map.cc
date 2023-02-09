#include <mysym/mysym.h>

namespace mysym
{
  symbol_t map(fptr_map_t fmap, const symbol_t &s)
  {
    if (is_monomial(s))
      return s;

    symbol_t u = create(s.opt);
    for (auto it = s.items.begin(); it != s.items.end(); it++)
    {
      append(u, fmap(*it));
    }
    return u;
  }

  symbol_t map(const symbol_t &u, const symbol_t &s, opt_t o)
  {
    if (is_monomial(s) || is_monomial(u))
      return s;

    symbol_t v = create(u.opt);
    opt_t opt = (o == kOptNone ? kOptMul : o);
    for (auto it1 = u.items.begin(); it1 != u.items.end(); it1++)
    {
      for (auto it2 = s.items.begin(); it2 != s.items.end(); it2++)
      {
        // std::cout << print_string(*it1) << std::endl;
        // std::cout << print_string(*it2) << std::endl;
        append(v, make(opt, *it1, *it2));
      }
    }
    return v;
  }
} // namespace mysym