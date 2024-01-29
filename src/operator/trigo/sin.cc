#include <mysym/mysym.h>

namespace mysym
{
  static bool __sin_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __sin_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __sin(const symbol_t &x)
  {
    return just_make1(kOptSin, x);
  }

  symbol_t sin(const symbol_t &x)
  {
    return execute_cases(kOptSin, x);
  }

  void register_sin_rule()
  {
    register_case(kOptSin, "all", __sin);

    // 添加预处理与置后处理
    register_preprocess(kOptSin, __sin_preprocess);
    register_postprocess(kOptSin, __sin_postprocess);
  }

} // namespace mysym