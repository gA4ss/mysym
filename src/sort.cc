#include <mysym/mysym.h>

namespace mysym
{
  // /* 1.次数越低越在前
  //  * 2.项数越多越在前
  //  * 3.
  //  */
  // static bool __cmp(symbol_ptr_t s1, symbol_ptr_t s2)
  // {
  //   return true;
  // }

  // static bool __reverse_cmp(symbol_ptr_t s1, symbol_ptr_t s2)
  // {
  //   return !__cmp(s1, s2);
  // }

  // symbol_ptr_t sort(symbol_ptr_t s, bool reverse)
  // {
  //   if (reverse)
  //     std::sort(s->next.begin(), s->next.end(), __reverse_cmp);
  //   else
  //     std::sort(s->next.begin(), s->next.end(), __cmp);
  //   return s;
  // }
} // namespace mysym