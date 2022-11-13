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

  void merge_same_operator(symbol_ptr_t s)
  {
    //
    // 1.是单个符号并且不是基础运算符（常量，变量，函数）
    // 2.单目运算符
    // 直接返回，不进行处理
    //
    if (((is_single(s)) && (!is_operator(s->opt))) || (is_unary_operation(s)))
      return;
    
    symbol_link_t new_links;
    opt_t opt = s->opt;
    symbol_ptr_t p = nullptr;
    for (symbol_link_iter_t it = s->next.begin(); it < s->next.end(); it++)
    {
      merge_same_operator(*it);
      if ((*it)->opt == opt)
      {
        new_links.insert(new_links.end(), (*it)->next.begin(), (*it)->next.end());
      }
      else
      {
        new_links.push_back(*it);
      }
    }
    s->next = new_links;
    return;
  }
} // namespace mysym