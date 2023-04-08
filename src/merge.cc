#include <mysym/mysym.h>

namespace mysym
{
  void merge(symbol_t &s)
  {
    symbol_items_t new_items;
    opt_t opt = s.opt;
    for (auto it = s.items.begin(); it != s.items.end(); it++)
    {
      //
      // 这里允许对子项进行合并，为了
      // f((x+(y+z)), 1)，这种情况。
      //
      merge(*it);

      // 判断当前运算符是否一致
      if ((*it).opt == opt)
      {
        //
        // 判断当运算是否符合结合律
        // 如果不符合则直接压入子项
        // 目，为了最后直接替换的代
        // 码统一掉。
        //
        if (opt_associative_law(kind(s)))
          new_items.insert(new_items.end(), (*it).items.begin(), (*it).items.end());
        else
          new_items.push_back(*it);
      }
      else
      {
        new_items.push_back(*it);
      }
    }
    s.items = new_items;
    return;
  }
} // namespace mysym