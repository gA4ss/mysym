#include <mysym/mysym.h>

namespace mysym
{
  static bool __arccosh_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arccosh_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arccosh(const symbol_t &x)
  {
    return just_make1(kOptArcCosh, x);
  }

  symbol_t arccosh(const symbol_t &x)
  {
    return execute_cases(kOptArcCosh, x);
  }

  void register_arccosh_rule()
  {
    register_case(kOptArcCosh, "all", __arccosh);

    // 添加预处理与置后处理
    register_preprocess(kOptArcCosh, __arccosh_preprocess);
    register_postprocess(kOptArcCosh, __arccosh_postprocess);
  }

} // namespace mysym