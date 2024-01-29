#include <mysym/mysym.h>

namespace mysym
{
  static bool __arccsc_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arccsc_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arccsc(const symbol_t &x)
  {
    return just_make1(kOptArcCsc, x);
  }

  symbol_t arccsc(const symbol_t &x)
  {
    return execute_cases(kOptArcCsc, x);
  }

  void register_arccsc_rule()
  {
    register_case(kOptArcCsc, "all", __arccsc);

    // 添加预处理与置后处理
    register_preprocess(kOptArcCsc, __arccsc_preprocess);
    register_postprocess(kOptArcCsc, __arccsc_postprocess);
  }

} // namespace mysym