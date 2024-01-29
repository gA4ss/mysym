#include <mysym/mysym.h>

namespace mysym
{
  static bool __symbol_cmp(const symbol_t &s1, const symbol_t &s2)
  {
    int c = compare(s1, s2);
    return (c == -1) ? true : false;
  }

  static void __sort(symbol_t &x)
  {
    if ((symbol_size(x) == 0) || (!is_basic(kind(x))))
      return;

    //
    // 排序
    //
    std::sort(x.items.begin(), x.items.end(), __symbol_cmp);

    // 应用子序列
    for (auto it = x.items.begin(); it != x.items.end(); it++)
    {
      __sort(*it);
    }

    return;
  }

  void sort(symbol_t &s, bool reverse)
  {
    if ((symbol_size(s) == 0) || (!is_basic(kind(s))))
      return;

    __sort(s);

    //
    // 逆向顺序
    //
    if (reverse)
    {
      std::reverse(s.items.begin(), s.items.end());
      // 对子序列进行反转
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
        if (it->items.size())
          std::reverse(it->items.begin(), it->items.end());
      }
    }
    return;
  }
} // namespace mysym