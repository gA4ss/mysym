#include <mysym/mysym.h>

namespace mysym
{
  static bool __arccos_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arccos_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arccos(const symbol_t &x)
  {
    return just_make1(kOptArcCos, x);
  }

  symbol_t arccos(const symbol_t &x)
  {
    return execute_cases(kOptArcCos, x);
  }

  void register_arccos_rule()
  {
    register_case(kOptArcCos, "all", __arccos);

    // 添加预处理与置后处理
    register_preprocess(kOptArcCos, __arccos_preprocess);
    register_postprocess(kOptArcCos, __arccos_postprocess);
  }

} // namespace mysym