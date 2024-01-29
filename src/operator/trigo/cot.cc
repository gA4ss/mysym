#include <mysym/mysym.h>

namespace mysym
{
  static bool __cot_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __cot_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __cot(const symbol_t &x)
  {
    return just_make1(kOptCot, x);
  }

  symbol_t cot(const symbol_t &x)
  {
    return execute_cases(kOptCot, x);
  }

  void register_cot_rule()
  {
    register_case(kOptCot, "all", __cot);

    // 添加预处理与置后处理
    register_preprocess(kOptCot, __cot_preprocess);
    register_postprocess(kOptCot, __cot_postprocess);
  }

} // namespace mysym