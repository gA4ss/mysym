#include <mysym/mysym.h>

namespace mysym
{
  static bool __coth_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __coth_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __coth(const symbol_t &x)
  {
    return just_make1(kOptCoth, x);
  }

  symbol_t coth(const symbol_t &x)
  {
    return execute_cases(kOptCoth, x);
  }

  void register_coth_rule()
  {
    register_case(kOptCoth, "all", __coth);

    // 添加预处理与置后处理
    register_preprocess(kOptCoth, __coth_preprocess);
    register_postprocess(kOptCoth, __coth_postprocess);
  }

} // namespace mysym