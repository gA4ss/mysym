#include <mysym/mysym.h>

namespace mysym
{
  void sort(symbol_t &s, bool reverse)
  {
    apply_commutative_law(s);

    if (symbol_size(s) == 0)
      return;

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