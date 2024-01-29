#include <mysym/mysym.h>

namespace mysym
{
  static bool __arcsech_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arcsech_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arcsech(const symbol_t &x)
  {
    return just_make1(kOptArcSech, x);
  }

  symbol_t arcsech(const symbol_t &x)
  {
    return execute_cases(kOptArcSech, x);
  }

  void register_arcsech_rule()
  {
    register_case(kOptArcSech, "all", __arcsech);

    // 添加预处理与置后处理
    register_preprocess(kOptArcSech, __arcsech_preprocess);
    register_postprocess(kOptArcSech, __arcsech_postprocess);
  }

} // namespace mysym