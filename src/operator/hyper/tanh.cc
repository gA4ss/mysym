#include <mysym/mysym.h>

namespace mysym
{
  static bool __tanh_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __tanh_postprocess(const symbol_t &z)
  {
    return z;
  }

  static symbol_t __tanh(const symbol_t &x)
  {
    return just_make1(kOptTanh, x);
  }

  symbol_t tanh(const symbol_t &x)
  {
    return execute_cases(kOptTanh, x);
  }

  void register_tanh_rule()
  {
    register_case(kOptTanh, "all", __tanh);

    // 添加预处理与置后处理
    register_preprocess(kOptTanh, __tanh_preprocess);
    register_postprocess(kOptTanh, __tanh_postprocess);
  }

} // namespace mysym