#include <mysym/mysym.h>

namespace mysym
{
  static bool __cos_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __cos_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __cos(const symbol_t &x)
  {
    return just_make1(kOptCos, x);
  }

  symbol_t cos(const symbol_t &x)
  {
    return execute_cases(kOptCos, x);
  }

  void register_cos_rule()
  {
    register_case(kOptCos, "all", __cos);

    // 添加预处理与置后处理
    register_preprocess(kOptCos, __cos_preprocess);
    register_postprocess(kOptCos, __cos_postprocess);
  }

} // namespace mysym