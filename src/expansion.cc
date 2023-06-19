#include <mysym/mysym.h>

namespace mysym
{
  static inline symbol_t __expansion_mul(const symbol_t &s)
  {
    return s;
  }

  static inline symbol_t __expansion_pow(const symbol_t &s)
  {
    if (symbol_is_integer(exponent(s)))
    {
      symbol_t u = create_opt(kOptMul);
      symbol_t b = base(s);
      // number_t n = symbol_to_number(s);
      // while (n > 1)
      // {
        
      // }
    }
    return s;
  }

  symbol_t expansion(const symbol_t &s)
  {
    if (is_mul(kind(s)))
    {
      return __expansion_mul(s);
    }
    else if (is_pow(kind(s)))
    {
      return __expansion_pow(s);
    }
    return s;
  }
} // namespace mysym