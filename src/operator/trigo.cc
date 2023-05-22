#include <mysym/mysym.h>

// trigonometric
namespace mysym
{
  symbol_t sin(const symbol_t &x)
  {
    return default_func_handler(kOptSin, x);
  }

  symbol_t cos(const symbol_t &x)
  {
    return default_func_handler(kOptCos, x);
  }

  symbol_t tan(const symbol_t &x)
  {
    return default_func_handler(kOptTan, x);
  }

  symbol_t cot(const symbol_t &x)
  {
    return default_func_handler(kOptCot, x);
  }

  symbol_t sec(const symbol_t &x)
  {
    return default_func_handler(kOptSec, x);
  }

  symbol_t csc(const symbol_t &x)
  {
    return default_func_handler(kOptCsc, x);
  }

  symbol_t arcsin(const symbol_t &x)
  {
    return default_func_handler(kOptArcSin, x);
  }

  symbol_t arccos(const symbol_t &x)
  {
    return default_func_handler(kOptArcCos, x);
  }

  symbol_t arctan(const symbol_t &x)
  {
    return default_func_handler(kOptArcTan, x);
  }

  symbol_t arccot(const symbol_t &x)
  {
    return default_func_handler(kOptArcCot, x);
  }

  symbol_t arcsec(const symbol_t &x)
  {
    return default_func_handler(kOptArcSec, x);
  }

  symbol_t arccsc(const symbol_t &x)
  {
    return default_func_handler(kOptArcCsc, x);
  }
} // namespace mysym