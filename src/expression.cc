#include <mysym/mysym.h>

namespace mysym
{
  list_t complete_sub_expressions(const symbol_t &s, bool found)
  {
    list_t l;

    // 单一符号直接退出
    if (is_sym(kind(s)))
    {
      insert(l, s, found);
      return l;
    }

    // 插入最开始的符号多项式，随后遍历它
    insert(l, s);
    for (auto it = s.items.begin(); it != s.items.end(); it++)
    {
      insert(l, complete_sub_expressions(*it, found), found);
    }

    return l;
  }
} // namespace mysym