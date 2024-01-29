#include <mysym/mysym.h>

namespace mysym
{
  static bool __csc_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __csc_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __csc(const symbol_t &x)
  {
    return just_make1(kOptCsc, x);
  }

  symbol_t csc(const symbol_t &x)
  {
    return execute_cases(kOptCsc, x);
  }

  void register_csc_rule()
  {
    register_case(kOptCsc, "all", __csc);

    // 添加预处理与置后处理
    register_preprocess(kOptCsc, __csc_preprocess);
    register_postprocess(kOptCsc, __csc_postprocess);
  }

} // namespace mysym