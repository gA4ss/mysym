#include <mysym/mysym.h>

namespace mysym
{
  static bool __fact_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __fact_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  static symbol_t __fact(const symbol_t &x)
  {
    return just_make1(kOptFact, x);
  }

  symbol_t fact(const symbol_t &x)
  {
    return execute_cases(kOptFact, x);
  }

  void register_fact_rule()
  {
    register_case(kOptFact, "atom", __fact);

    // 添加预处理与置后处理
    register_preprocess(kOptFact, __fact_preprocess);
    register_postprocess(kOptFact, __fact_postprocess);
  }

} // namespace mysym