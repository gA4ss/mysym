#include <mysym/mysym.h>

namespace mysym
{
  static bool __symbol_cmp(const symbol_t &s1, const symbol_t &s2)
  {
    int c = cmp(s1, s2);
    return (c == -1) ? true : false;
  }

  static bool __symbol_reverse_cmp(const symbol_t &s1, const symbol_t &s2)
  {
    return !__symbol_cmp(s1, s2);
  }

  void sort(symbol_t &s, bool reverse)
  {
    if (symbol_size(s) == 0)
      return;

    //
    // 双参数函数不进行排序，但是参数自身参加排序
    //
    if (!is_2ps_func(kind(s)))
    {
      if (reverse)
        std::sort(s.items.begin(), s.items.end(), __symbol_reverse_cmp);
      else
        std::sort(s.items.begin(), s.items.end(), __symbol_cmp);
    }

    //
    // 对子序列进行排序
    //
    for (auto it = s.items.begin(); it != s.items.end(); it++)
    {
      sort(*it, reverse);
    }

    return;
  }
} // namespace mysym