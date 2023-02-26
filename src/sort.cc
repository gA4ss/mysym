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
    if (is_sym(kind(s)))
      return;

    if (reverse)
      std::sort(s.items.begin(), s.items.end(), __symbol_reverse_cmp);
    else
      std::sort(s.items.begin(), s.items.end(), __symbol_cmp);
    return;
  }
} // namespace mysym