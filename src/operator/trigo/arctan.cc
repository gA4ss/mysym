#include <mysym/mysym.h>

namespace mysym
{
  static bool __arctan_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arctan_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arctan(const symbol_t &x)
  {
    return just_make1(kOptArcTan, x);
  }

  symbol_t arctan(const symbol_t &x)
  {
    return execute_cases(kOptArcTan, x);
  }

  void register_arctan_rule()
  {
    register_case(kOptArcTan, "all", __arctan);

    // 添加预处理与置后处理
    register_preprocess(kOptArcTan, __arctan_preprocess);
    register_postprocess(kOptArcTan, __arctan_postprocess);
  }

} // namespace mysym