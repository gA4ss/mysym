#include <mysym/mysym.h>

namespace mysym
{
  static bool __sinh_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __sinh_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __sinh(const symbol_t &x)
  {
    return just_make1(kOptSinh, x);
  }

  symbol_t sinh(const symbol_t &x)
  {
    return execute_cases(kOptSinh, x);
  }

  void register_sinh_rule()
  {
    register_case(kOptSinh, "all", __sinh);

    // 添加预处理与置后处理
    register_preprocess(kOptSinh, __sinh_preprocess);
    register_postprocess(kOptSinh, __sinh_postprocess);
  }

} // namespace mysym