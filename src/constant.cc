#include <mysym/mysym.h>

namespace mysym
{
  symbol_t constant(const symbol_t &s)
  {
    if (is_sym(kind(s)) || (is_add(kind(s))) || is_func(kind(s)))
      return create_int("1");

    if (is_const(kind(s)))
      return s;

    //
    // 到这里只剩乘法操作
    // 排序与自动化简保证了，第一个参数是常数。
    //
    if (is_const(kind(operand(s, 0))))
    {
      return operand(s, 0);
    }

    return create_int("1");
  }
} // namespace mysym