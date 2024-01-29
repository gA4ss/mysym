#include <mysym/mysym.h>

namespace mysym
{
  static bool __arcsinh_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arcsinh_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arcsinh(const symbol_t &x)
  {
    return just_make1(kOptArcSinh, x);
  }

  symbol_t arcsinh(const symbol_t &x)
  {
    return execute_cases(kOptArcSinh, x);
  }

  void register_arcsinh_rule()
  {
    register_case(kOptArcSinh, "all", __arcsinh);

    // 添加预处理与置后处理
    register_preprocess(kOptArcSinh, __arcsinh_preprocess);
    register_postprocess(kOptArcSinh, __arcsinh_postprocess);
  }

} // namespace mysym