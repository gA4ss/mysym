#include <mysym/mysym.h>

namespace mysym
{
  static bool __sec_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __sec_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __sec(const symbol_t &x)
  {
    return just_make1(kOptSec, x);
  }

  symbol_t sec(const symbol_t &x)
  {
    return execute_cases(kOptSec, x);
  }

  void register_sec_rule()
  {
    register_case(kOptSec, "all", __sec);

    // 添加预处理与置后处理
    register_preprocess(kOptSec, __sec_preprocess);
    register_postprocess(kOptSec, __sec_postprocess);
  }

} // namespace mysym