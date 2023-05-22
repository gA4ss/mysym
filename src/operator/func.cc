#include <mysym/mysym.h>

namespace mysym
{
  symbol_t default_func_handler(opt_t opt, const symbol_t &x)
  {
    symbol_t _x = x;
    apply_rule(_x);
    symbol_t y = create(opt);
    append(y, _x);
    return y;
  }

  symbol_t default_func_handler(opt_t opt, const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x = x, _y = y;
    apply_rule(_x);
    apply_rule(_y);
    symbol_t z = create(opt);
    append(z, _x); append(z, _y);
    return z;
  }


  static symbol_t __default_func_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    for (auto it = _x.items.begin(); it != _x.items.end(); it++)
    {
      apply_rule(*it);
    }
    return _x;
  }

  void register_func_rule()
  {
    append_entry(kOptAbs, __default_func_entry);
    append_entry(kOptFact, __default_func_entry);
    append_entry(kOptFrac, frac_entry);
    append_entry(kOptMod, __default_func_entry);
    append_entry(kOptPow, __default_func_entry);
    append_entry(kOptLog, __default_func_entry);
    append_entry(kOptSin, __default_func_entry);
    append_entry(kOptCos, __default_func_entry);
    append_entry(kOptTan, __default_func_entry);
    append_entry(kOptCot, __default_func_entry);
    append_entry(kOptSec, __default_func_entry);
    append_entry(kOptCsc, __default_func_entry);
    append_entry(kOptArcSin, __default_func_entry);
    append_entry(kOptArcCos, __default_func_entry);
    append_entry(kOptArcTan, __default_func_entry);
    append_entry(kOptArcCot, __default_func_entry);
    append_entry(kOptArcSec, __default_func_entry);
    append_entry(kOptArcCsc, __default_func_entry);
    append_entry(kOptSinh, __default_func_entry);
    append_entry(kOptCosh, __default_func_entry);
    append_entry(kOptTanh, __default_func_entry);
    append_entry(kOptCoth, __default_func_entry);
    append_entry(kOptSech, __default_func_entry);
    append_entry(kOptCsch, __default_func_entry);
    append_entry(kOptArcSinh, __default_func_entry);
    append_entry(kOptArcCosh, __default_func_entry);
    append_entry(kOptArcTanh, __default_func_entry);
    append_entry(kOptArcCoth, __default_func_entry);
    append_entry(kOptArcSech, __default_func_entry);
    append_entry(kOptArcCsch, __default_func_entry);
  }
} // namespace mysym