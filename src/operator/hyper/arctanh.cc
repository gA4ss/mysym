#include <mysym/mysym.h>

namespace mysym
{
  static bool __arctanh_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arctanh_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arctanh(const symbol_t &x)
  {
    return just_make1(kOptArcTanh, x);
  }

  symbol_t arctanh(const symbol_t &x)
  {
    return execute_cases(kOptArcTanh, x);
  }

  void register_arctanh_rule()
  {
    register_case(kOptArcTanh, "all", __arctanh);

    // 添加预处理与置后处理
    register_preprocess(kOptArcTanh, __arctanh_preprocess);
    register_postprocess(kOptArcTanh, __arctanh_postprocess);
  }

} // namespace mysym