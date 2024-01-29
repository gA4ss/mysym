#include <mysym/mysym.h>

namespace mysym
{
  static bool __arccot_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arccot_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arccot(const symbol_t &x)
  {
    return just_make1(kOptArcCot, x);
  }

  symbol_t arccot(const symbol_t &x)
  {
    return execute_cases(kOptArcCot, x);
  }

  void register_arccot_rule()
  {
    register_case(kOptArcCot, "all", __arccot);

    // 添加预处理与置后处理
    register_preprocess(kOptArcCot, __arccot_preprocess);
    register_postprocess(kOptArcCot, __arccot_postprocess);
  }

} // namespace mysym