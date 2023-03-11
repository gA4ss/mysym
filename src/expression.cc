#include <mysym/mysym.h>

namespace mysym
{
  list_t complete_sub_expressions(const symbol_t &s, bool found)
  {
    list_t l;

    // 单一符号直接退出
    if (is_sym(kind(s)))
    {
      append(l, s, found);
      return l;
    }

    // 插入最开始的符号多项式，随后遍历它
    append(l, s);
    for (auto it = s.items.begin(); it != s.items.end(); it++)
    {
      append(l, complete_sub_expressions(*it, found), found);
    }

    return l;
  }

  bool free_of(const symbol_t &s, const symbol_t &u)
  {
    if (cmp(s, u) == 0)
      return false;
    
    for (auto it = s.items.begin(); it != s.items.end(); it++)
    {
      if (!free_of(*it, u))
        return false;
    }
    return true;
  }

  bool free_of(const symbol_t &s, const list_t &xs)
  {
    for (auto it = xs.begin(); it != xs.end(); it++)
    {
      if (!free_of(s, *it))
        return false;
    }
    return true;
  }
} // namespace mysym