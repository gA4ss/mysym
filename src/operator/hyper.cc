#include <mysym/mysym.h>

// trigonometric
namespace mysym
{
  symbol_t sinh(const symbol_t &x)
  {
    return default_func_handler(kOptSinh, x);
  }

  symbol_t cosh(const symbol_t &x)
  {
    return default_func_handler(kOptCosh, x);
  }

  symbol_t tanh(const symbol_t &x)
  {
    return default_func_handler(kOptTanh, x);
  }

  symbol_t coth(const symbol_t &x)
  {
    return default_func_handler(kOptCoth, x);
  }

  symbol_t sech(const symbol_t &x)
  {
    return default_func_handler(kOptSech, x);
  }

  symbol_t csch(const symbol_t &x)
  {
    return default_func_handler(kOptCsch, x);
  }

  symbol_t arcsinh(const symbol_t &x)
  {
    return default_func_handler(kOptArcSinh, x);
  }

  symbol_t arccosh(const symbol_t &x)
  {
    return default_func_handler(kOptArcCosh, x);
  }

  symbol_t arctanh(const symbol_t &x)
  {
    return default_func_handler(kOptArcTanh, x);
  }

  symbol_t arccoth(const symbol_t &x)
  {
    return default_func_handler(kOptArcCoth, x);
  }

  symbol_t arcsech(const symbol_t &x)
  {
    return default_func_handler(kOptArcSech, x);
  }

  symbol_t arccsch(const symbol_t &x)
  {
    return default_func_handler(kOptArcCsch, x);
  }
} // namespace mysym