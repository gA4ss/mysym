#include <mysym/mysym.h>

namespace mysym
{
  // static bool __erase_from_symbol_ptr(symbol_link_t links, symbol_ptr_t s)
  // {
  //   auto it = std::find(links.begin(), links.end(), s);
  //   if (it != links.end())
  //   {
  //     links.erase(it);
  //     return true;
  //   }
  //   return false;
  // }

  void merge_same_basic_operator(symbol_t& s)
  {
    //
    // 1.是单个符号并且不是基础运算符（常量，变量，函数）
    // 2.单目运算符
    // 直接返回，不进行处理
    //
    if (((is_single(s)) && (!is_basic(s.opt))) || (is_unary_operation(s)))
      return;

    symbol_items_t new_items;
    opt_t opt = s.opt;
    for (auto it = s.items.begin(); it != s.items.end(); it++)
    {
      merge_same_basic_operator(*it);
      if ((*it).opt == opt)
      {
        new_items.insert(new_items.end(), (*it).items.begin(), (*it).items.end());
      }
      else
      {
        new_items.push_back(*it);
      }
    }
    s.items = new_items;
    return;
  }

  void merge(symbol_t& s)
  {
    // 如果是单项式则直接返回
    if (is_monomial(s))
      return;

    //
    // 合并相同的基础运算符
    //
    merge_same_basic_operator(s);
    return;
  }
} // namespace mysym