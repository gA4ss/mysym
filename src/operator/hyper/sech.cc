#include <mysym/mysym.h>

namespace mysym
{
  static bool __sech_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __sech_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __sech(const symbol_t &x)
  {
    return just_make1(kOptSech, x);
  }

  symbol_t sech(const symbol_t &x)
  {
    return execute_cases(kOptSech, x);
  }

  void register_sech_rule()
  {
    register_case(kOptSech, "all", __sech);

    // 添加预处理与置后处理
    register_preprocess(kOptSech, __sech_preprocess);
    register_postprocess(kOptSech, __sech_postprocess);
  }

} // namespace mysym