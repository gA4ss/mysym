#include <mysym/mysym.h>

namespace mysym
{
  static bool __csch_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __csch_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __csch(const symbol_t &x)
  {
    return just_make1(kOptCsch, x);
  }

  symbol_t csch(const symbol_t &x)
  {
    return execute_cases(kOptCsch, x);
  }

  void register_csch_rule()
  {
    register_case(kOptCsch, "all", __csch);

    // 添加预处理与置后处理
    register_preprocess(kOptCsch, __csch_preprocess);
    register_postprocess(kOptCsch, __csch_postprocess);
  }

} // namespace mysym