#include <mysym/mysym.h>

namespace mysym
{
  symbol_t map(fptr_map_t fmap, const symbol_t &s)
  {
    if (is_atom(kind(s)))
      return fmap(s);

    symbol_t u = create(s.opt);
    for (auto it = s.items.begin(); it != s.items.end(); it++)
    {
      append(u, fmap(*it));
    }
    return u;
  }

  symbol_t map(const symbol_t &u, const symbol_t &s, opt_t o, bool ex)
  {
    opt_t opt = (o == kOptNone ? kOptMul : o);
    if (is_sym(kind(u)))
    {
      return make(opt, u, s);
    }

    symbol_t v = create(u.opt);
    for (auto it1 = u.items.begin(); it1 != u.items.end(); it1++)
    {
      if (ex)
      {
        if (is_sym(kind(s)))
        {
          append(v, make(opt, *it1, s));
        }
        else
        {
          for (auto it2 = s.items.begin(); it2 != s.items.end(); it2++)
          {
            // std::cout << print_string(*it1) << std::endl;
            // std::cout << print_string(*it2) << std::endl;
            append(v, make(opt, *it1, *it2));
          }
        }
      }
      else
      {
        append(v, make(opt, *it1, s));
      }
    }
    return v;
  }
} // namespace mysym