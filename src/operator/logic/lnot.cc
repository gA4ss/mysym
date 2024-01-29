#include <mysym/mysym.h>

namespace mysym
{
  static bool __lnot_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __lnot_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __lnot(const symbol_t &x)
  {
    return just_make1(kOptNot, x);
  }

  symbol_t lnot(const symbol_t &x)
  {
    return execute_cases(kOptNot, x);
  }

  void register_lnot_rule()
  {
    register_case(kOptNot, "all", __lnot);

    // 添加预处理与置后处理
    register_preprocess(kOptNot, __lnot_preprocess);
    register_postprocess(kOptNot, __lnot_postprocess);
  }

} // namespace mysym