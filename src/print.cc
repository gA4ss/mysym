#include <mysym/mysym.h>

namespace mysym
{
  static std::string __print_unary_operation(const symbol_t &s)
  {
    if (!is_unary_operation(s))
      return "";

    std::string str = opt_name(s.opt);
    str += print_string(s.items[0]);
    return str;
  }

  static std::string __print_multiple_operation(const symbol_t &s)
  {
    if (is_unary_operation(s))
      return "";

    symbol_t p;
    std::string str = "";
    size_t l = symbol_size(s);
    for (size_t i = 0; i < l; i++)
    {
      p = s.items[i];

      if ((is_single(p)) || is_func(p.opt))
      {
        str += print_string(p);
      }
      else
      {
        //
        // 判断优先级
        //
        if (cmp_operator_priority(s.opt, p.opt) > 0)
        {
          str += '(';
          str += print_string(p);
          str += ')';
        }
        else
        {
          str += print_string(p);
        }
      }

      // 链接符号
      if (i != l - 1)
        str += opt_name(s.opt);
    }
    return str;
  }

  std::string print_string(const symbol_t &s)
  {
    std::string str = "";
    if (is_basic(s.opt))
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
      if (is_func(s.opt))
      {
        str = s.literal;
        str += "(";

        for (auto it = s.items.begin(); it != s.items.end(); it++)
        {
          str += print_string(*it);
          str += ",";
        }

        str.pop_back(); // 删除最后一个","号
        str += ")";
      }
      else if (is_none(s.opt))
      {
        str = opt_name(s.opt);
      }
      else if (is_frac(s.opt))
      {
        str = numerator(s).literal;
        str += "/";
        str += denominator(s).literal;
      }
      else
      {
        str = s.literal;
      }
    }
    return str;
  }

  std::string print_string(const list_t &l)
  {
    if (size(l) == 0)
      return "{}";

    std::string str = "{";
    for (auto it = l.begin(); it != l.end(); it++)
    {
      str += print_string(*it);
      str += ",";
    }
    str.pop_back(); // 删除最后一个","号
    return str + "}";
  }

  std::string print_string(const optset_t& s)
  {
    std::string str;
    for (auto it = s.items.elements.begin(); it != s.items.elements.end(); it++)
    {
      str += (it->first + ',');
    }
    str.pop_back();
    return str;
  }

  std::string print_string(const optcase_t& s)
  {
    std::string str;
    for (auto it = s.begin(); it != s.end(); it++)
    {
      str += (*it + '\n');
    }
    // str.pop_back();
    return str;
  }
} // namespace mysym