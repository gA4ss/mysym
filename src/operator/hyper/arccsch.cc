#include <mysym/mysym.h>

namespace mysym
{
  static bool __arccsch_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arccsch_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arccsch(const symbol_t &x)
  {
    return just_make1(kOptArcCsch, x);
  }

  symbol_t arccsch(const symbol_t &x)
  {
    return execute_cases(kOptArcCsch, x);
  }

  void register_arccsch_rule()
  {
    register_case(kOptArcCsch, "all", __arccsch);

    // 添加预处理与置后处理
    register_preprocess(kOptArcCsch, __arccsch_preprocess);
    register_postprocess(kOptArcCsch, __arccsch_postprocess);
  }

} // namespace mysym