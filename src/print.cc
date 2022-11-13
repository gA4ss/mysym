#include <mysym/mysym.h>

namespace mysym
{
  static std::string __print_unary_operation(symbol_ptr_t s)
  {
    if (!is_unary_operation(s))
      return "";

    std::string str = ret_name(s->opt);
    str += print_string(s->next[0]);
    return str;
  }

  static std::string __print_multiple_operation(symbol_ptr_t s)
  {
    if (is_unary_operation(s))
      return "";

    std::string str = "";
    symbol_ptr_t p = nullptr;
    size_t l = link_size(s);
    for (size_t i = 0; i < l; i++)
    {
      p = s->next[i];
      if ((is_single(p)) || is_elm_func(p->opt))
      {
        str += print_string(p);
      }
      else
      {
        str += '(';
        str += print_string(p);
        str += ')';
      }

      // 链接符号
      if (i != l - 1)
        str += ret_name(s->opt);
    }
    return str;
  }

  std::string print_string(symbol_ptr_t s)
  {
    std::string str = "";
    if (is_operator(s->opt))
    {
      //
      // 判断是单目运算还是多目运算
      //
      if (is_unary_operation(s))
      {
        str = __print_unary_operation(s);
      }
      else
      {
        str = __print_multiple_operation(s);
      }
    }
    else
    {
      if (is_func(s->opt))
      {
        str = s->name;
        str += "(";
        if (is_elm_func(s->opt))
        {
          if (link_size(s) != 2)
          {
            mysym_invalid_range_in_params_exception("number of params = %d", link_size(s));
          }
          str += s->next[0]->name;
          str += ",";
          str += s->next[1]->name;
        }
        else
        {
          size_t l = link_size(s);
          for (size_t i = 0; i < l; i++)
          {
            str += s->next[0]->name;
            if (i != l - 1)
              str += ",";
          }
        }
        str += ")";
      }
      else
      {
        str = s->name;
      }
    }
    return str;
  }
} // namespace mysym