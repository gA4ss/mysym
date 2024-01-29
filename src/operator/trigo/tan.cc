#include <mysym/mysym.h>

namespace mysym
{
  static bool __tan_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __tan_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __tan(const symbol_t &x)
  {
    return just_make1(kOptTan, x);
  }

  symbol_t tan(const symbol_t &x)
  {
    return execute_cases(kOptTan, x);
  }

  void register_tan_rule()
  {
    register_case(kOptTan, "all", __tan);

    // 添加预处理与置后处理
    register_preprocess(kOptTan, __tan_preprocess);
    register_postprocess(kOptTan, __tan_postprocess);
  }

} // namespace mysym