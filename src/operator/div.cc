#include <mysym/mysym.h>
#include <mynum/wrapper.h>
#include "__test.h"

namespace mysym
{

  static inline symbol_t __polynomial_div(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    return z;
  }

  symbol_t div(const symbol_t &x, const symbol_t &y)
  {
    symbol_t a = x, b = y;
    symbol_t c;

    // 进行各种类型的除法
    if (compare(a, b) == 0)
    {
      return gConstOne;
    }
    else if ((is_num(kind(a))) && (is_num(kind(b))))
    {
      return number_to_symbol(symbol_to_number(a) / symbol_to_number(b));
    }
    else if ((is_basic(kind(a))) || (is_basic(kind(b))))
    {
      return __polynomial_div(a, b);
    }

    //
    // 其余情况直接用指数操作合成
    //
    b = execute_cases(kOptPow, b, gConstNegOne);
    c = execute_cases(kOptMul, a, b);
    // 对结果排序
    sort(c);
    return c;
  }
} // namespace mysym