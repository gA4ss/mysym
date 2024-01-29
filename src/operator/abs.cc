#include <mysym/mysym.h>
#include "../__misc.h"

namespace mysym
{
  static bool __abs_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __abs_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __abs(const symbol_t &x)
  {
    // 对一些特殊值的处理
    if (is_neg_inf(kind(x)))
      return gConstInf;
    else if (compare(x, gConstZero) == 0)
      return x;

    if (sign(x) == kSignNegative)
    {
      return opposite(x);
    }
    return just_make1(kOptAbs, x);
  }

  symbol_t abs(const symbol_t &x)
  {
    return execute_cases(kOptAbs, x);
  }

  void register_abs_rule()
  {
    optset_t optset = create_optset_exclude(random_string(), kOptAdd);
    register_case(kOptAbs, optset.name, __abs);

    // 添加预处理与置后处理
    register_preprocess(kOptAbs, __abs_preprocess);
    register_postprocess(kOptAbs, __abs_postprocess);
  }

} // namespace mysym