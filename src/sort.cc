#include <mysym/mysym.h>

namespace mysym
{
  static bool __symbol_cmp(const symbol_t &s1, const symbol_t &s2)
  {
    int c = compare(s1, s2);
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
    // 符合交换律的才可以进行排序
    //
    if (!opt_commutative_law(kind(s)))
      return;

    if (reverse)
      std::sort(s.items.begin(), s.items.end(), __symbol_reverse_cmp);
    else
      std::sort(s.items.begin(), s.items.end(), __symbol_cmp);

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