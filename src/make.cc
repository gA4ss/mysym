#include <mysym/mysym.h>
#include <regex>

namespace mysym
{
  static bool __is_integer(std::string s)
  {
    return false;
  }

  static bool __is_real(std::string s)
  {
    return false;
  }

  static bool __is_number(std::string s)
  {
    return __is_integer(s) || __is_real(s);
  }

  static bool __is_variate(std::string s)
  {
    return false;
  }

  symbol_t make(opt_t opt, const symbol_t &s, bool nas)
  {
    symbol_t u = create_opt(opt);
    append(u, s);
    if (!nas)
      automatic_simplify(u);
    return u;
  }

  symbol_t make(opt_t opt, const symbol_t &s1, const symbol_t &s2, bool nas)
  {
    symbol_t u = create_opt(opt);
    append(u, s1);
    append(u, s2);
    if (!nas)
      automatic_simplify(u);
    return u;
  }

  symbol_t make(opt_t opt, std::string s, bool nas)
  {
    symbol_t v = create_var(s);
    return make(opt, v, nas);
  }

  symbol_t make(opt_t opt, std::string s1, std::string s2, bool nas)
  {
    symbol_t v1 = create_var(s1);
    symbol_t v2 = create_var(s2);
    return make(opt, v1, v2, nas);
  }

  symbol_t make(opt_t opt, std::string s1, const symbol_t &s2, bool nas)
  {
    symbol_t v1 = create_var(s1);
    return make(opt, v1, s2, nas);
  }

  symbol_t make(opt_t opt, const symbol_t &s1, std::string s2, bool nas)
  {
    symbol_t v2 = create_var(s2);
    return make(opt, s1, v2, nas);
  }

} // namespace mysym