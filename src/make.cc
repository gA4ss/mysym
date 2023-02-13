#include <mysym/mysym.h>

namespace mysym
{
  symbol_t make(opt_t opt, const symbol_t &s, bool as)
  {
    symbol_t u = create_opt(opt);
    append(u, s);
    if (as)
      automatic_simplify(u);
    return u;
  }

  symbol_t make(opt_t opt, const symbol_t &s1, const symbol_t &s2, bool as)
  {
    symbol_t u = create_opt(opt);
    append(u, s1);
    append(u, s2);
    if (as)
      automatic_simplify(u);
    return u;
  }

  symbol_t make(opt_t opt, std::string s, bool as)
  {
    symbol_t v = create_sym(s);
    return make(opt, v, as);
  }

  symbol_t make(opt_t opt, std::string s1, std::string s2, bool as)
  {
    symbol_t v1 = create_sym(s1);
    symbol_t v2 = create_sym(s2);
    return make(opt, v1, v2, as);
  }

  symbol_t make(opt_t opt, std::string s1, const symbol_t &s2, bool as)
  {
    symbol_t v1 = create_sym(s1);
    return make(opt, v1, s2, as);
  }

  symbol_t make(opt_t opt, const symbol_t &s1, std::string s2, bool as)
  {
    symbol_t v2 = create_sym(s2);
    return make(opt, s1, v2, as);
  }

} // namespace mysym