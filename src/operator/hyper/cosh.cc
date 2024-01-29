#include <mysym/mysym.h>

namespace mysym
{
  static bool __cosh_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __cosh_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __cosh(const symbol_t &x)
  {
    return just_make1(kOptCosh, x);
  }

  symbol_t cosh(const symbol_t &x)
  {
    return execute_cases(kOptCosh, x);
  }

  void register_cosh_rule()
  {
    register_case(kOptCosh, "all", __cosh);

    // 添加预处理与置后处理
    register_preprocess(kOptCosh, __cosh_preprocess);
    register_postprocess(kOptCosh, __cosh_postprocess);
  }

} // namespace mysym