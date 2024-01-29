#include <mysym/mysym.h>
#include <regex>

namespace mysym
{
  symbol_t make(opt_t opt, const symbol_t &s, bool nas)
  {
    symbol_t u = create_opt(opt);
    append(u, s);
    if (!nas)
      automatic_simplify(u);
#ifdef DEBUG
    u.dbgstr = print_string(u);
#endif
    return u;
  }

  symbol_t make(opt_t opt, const symbol_t &s1, const symbol_t &s2, bool nas)
  {
    symbol_t u;
    if (is_sub(opt))
    {
      symbol_t ns2 = create_opt(kOptMul);
      append(ns2, gConstNegOne);
      append(ns2, s2);
      u = create_opt(kOptAdd);
      append(u, s1);
      append(u, ns2);
    }
    else if (is_div(opt))
    {
      symbol_t ds2 = create_opt(kOptPow);
      append(ds2, s2);
      append(ds2, gConstNegOne);
      u = create_opt(kOptMul);
      append(u, s1);
      append(u, ds2);
    }
    else
    {
      u = create_opt(opt);
      append(u, s1);
      append(u, s2);
    }

    //
    // 自动化简
    //
    if (!nas)
      automatic_simplify(u);
#ifdef DEBUG
    u.dbgstr = print_string(u);
#endif
    return u;
  }

  symbol_t make(opt_t opt, std::string s, bool nas)
  {
    symbol_t v = create_sym(s);
    return make(opt, v, nas);
  }

  symbol_t make(opt_t opt, std::string s1, std::string s2, bool nas)
  {
    symbol_t v1 = create_sym(s1);
    symbol_t v2 = create_sym(s2);
    return make(opt, v1, v2, nas);
  }

  symbol_t make(opt_t opt, std::string s1, const symbol_t &s2, bool nas)
  {
    symbol_t v1 = create_sym(s1);
    return make(opt, v1, s2, nas);
  }

  symbol_t make(opt_t opt, const symbol_t &s1, std::string s2, bool nas)
  {
    symbol_t v2 = create_sym(s2);
    return make(opt, s1, v2, nas);
  }

} // namespace mysym