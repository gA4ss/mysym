#include <mysym/mysym.h>
#include <cctype>
#include <regex>

namespace mysym
{
  //   static int __count_digits(const std::string &s)
  //   {
  //     return std::count_if(s.begin(), s.end(),
  //                          [](unsigned char c)
  //                          { return std::isdigit(c); });
  //   }

  // #define __is_integer(s) ((s).length() == __count_digits(s))
  // #define __is_real(s) (((s).length() == __count_digits(s) - 1) && (s.find(".") != s.end()))

  static bool __check_integer_format(const std::string &s)
  {
    return true;
  }

  static bool __check_real_format(const std::string &s)
  {
    return true;
  }

  symbol_t create(opt_t opt, std::string literal)
  {
    symbol_t s;
    s.opt = opt;
    if (is_opt(opt))
    {
      s.literal = opt_name(opt);
      if (s.literal == "")
      {
        mysym_not_found_operator_exception("opt = %d", opt);
      }
    }
    else
    {
      if (opt == kOptInteger)
      {
        if (!__check_integer_format(literal))
        {
          mysym_invalid_symbol_format_exception("type = %d, literal = %s", opt, literal.c_str());
        }
      }
      else if (opt == kOptReal)
      {
        if (!__check_real_format(literal))
        {
          mysym_invalid_symbol_format_exception("type = %d, literal = %s", opt, literal.c_str());
        }
      }
      s.literal = literal;
    }
    return s;
  }
} // namespace mysym