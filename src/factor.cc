#include <mysym/mysym.h>

namespace mysym
{
  symbol_t gcd(const symbol_t &x)
  {
    return gConstUDF;
  }

  symbol_t gcd(const list_t &s)
  {
    return gConstUDF;
  }

  symbol_t lcm(const symbol_t &x)
  {
    return gConstUDF;
  }

  symbol_t lcm(const list_t &s)
  {
    return gConstUDF;
  }
  
  list_t extend_euclid(const list_t &s)
  {
    return {};
  }
} // namespace mysym