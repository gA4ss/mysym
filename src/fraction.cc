#include <mysym/mysym.h>

namespace mysym
{
  symbol_t numerator(const symbol_t &s)
  {
    if (kind(s) != kOptFrac)
      return s;
    return s.items[0];
  }

  symbol_t denominator(const symbol_t &s)
  {
    if (kind(s) != kOptFrac)
    {
      return create_int("1");
    }
    return s.items[1];
  }

  symbol_t frac_to_product(const symbol_t &s)
  {
    if (kind(s) != kOptFrac)
      return s;

    symbol_t p = frac(create_int("1"), denominator(s));
    symbol_t u = mul(p, numerator(s));
    return u;
  }
} // namespace mysym