#include <mysym/mysym.h>

namespace mysym
{
  static bool __arcsin_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arcsin_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arcsin(const symbol_t &x)
  {
    return just_make1(kOptArcSin, x);
  }

  symbol_t arcsin(const symbol_t &x)
  {
    return execute_cases(kOptArcSin, x);
  }

  void register_arcsin_rule()
  {
    register_case(kOptArcSin, "all", __arcsin);

    // 添加预处理与置后处理
    register_preprocess(kOptArcSin, __arcsin_preprocess);
    register_postprocess(kOptArcSin, __arcsin_postprocess);
  }

} // namespace mysym