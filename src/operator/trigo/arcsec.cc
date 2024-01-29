#include <mysym/mysym.h>

namespace mysym
{
  static bool __arcsec_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arcsec_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arcsec(const symbol_t &x)
  {
    return just_make1(kOptArcSec, x);
  }

  symbol_t arcsec(const symbol_t &x)
  {
    return execute_cases(kOptArcSec, x);
  }

  void register_arcsec_rule()
  {
    register_case(kOptArcSec, "all", __arcsec);

    // 添加预处理与置后处理
    register_preprocess(kOptArcSec, __arcsec_preprocess);
    register_postprocess(kOptArcSec, __arcsec_postprocess);
  }

} // namespace mysym