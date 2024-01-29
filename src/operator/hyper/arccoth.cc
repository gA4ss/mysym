#include <mysym/mysym.h>

namespace mysym
{
  static bool __arccoth_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __arccoth_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __arccoth(const symbol_t &x)
  {
    return just_make1(kOptArcCoth, x);
  }

  symbol_t arccoth(const symbol_t &x)
  {
    return execute_cases(kOptArcCoth, x);
  }

  void register_arccoth_rule()
  {
    register_case(kOptArcCoth, "all", __arccoth);

    // 添加预处理与置后处理
    register_preprocess(kOptArcCoth, __arccoth_preprocess);
    register_postprocess(kOptArcCoth, __arccoth_postprocess);
  }

} // namespace mysym