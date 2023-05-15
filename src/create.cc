#include <mysym/mysym.h>
#include <cctype>
#include <regex>

namespace mysym
{

#define __check_number_format(s) my::is_number(s)
#define __check_integer_format(s) my::is_integer(s)
#define __check_float_format(s) my::is_real(s)
#define __check_variate_format(s) my::is_variate(s)

  symbol_t create(opt_t opt, std::string literal)
  {
    symbol_t s;
    s.opt = opt;
    if (is_opt(opt) || is_nature(opt) || is_frac(opt))
    {
      s.literal = opt_name(opt);
      if (s.literal == "")
      {
        mysym_not_found_operator_exception("opt = %s", opt.c_str());
      }
    }
    else
    {
      if (opt == kOptVariate)
      {
        if (!__check_variate_format(literal))
        {
          mysym_invalid_symbol_format_exception("type = %d, literal = %s", opt.c_str(), literal.c_str());
        }
      }
      else if (opt == kOptNumber)
      {
        if (!__check_number_format(literal))
        {
          mysym_invalid_symbol_format_exception("type = %d, literal = %s", opt.c_str(), literal.c_str());
        }
      }
      s.literal = literal;
    }
    return s;
  }

  static std::regex __r_zero("^-?([0]+\\.[0]*|0+\\.0+|0)$");
  static std::regex __r_one("^1|1\\.[0]*$");
  static std::regex __r_neg_one("^-(1|1\\.[0]*)$");

#define __is_zero(literal) (std::regex_match(literal, __r_zero))
#define __is_one(literal) (std::regex_match(literal, __r_one))
#define __is_neg_one(literal) (std::regex_match(literal, __r_neg_one))
#define __is_pi(literal) (literal == "pi")
#define __is_e(literal) (literal == "e")
#define __is_inf(literal) (literal == "inf")
#define __is_neg_inf(literal) (literal == "-inf")

  symbol_t create_symbol(std::string literal)
  {
    symbol_t s;

    // 首先判断常数字符串
    if (__is_e(literal))
    {
      s.opt = kOptConstE;
      s.literal = opt_name(kOptConstE);
    }
    else if (__is_pi(literal))
    {
      s.opt = kOptConstPI;
      s.literal = opt_name(kOptConstPI);
    }
    else if (__is_inf(literal))
    {
      s.opt = kOptConstInf;
      s.literal = opt_name(kOptConstInf);
    }
    else if (__is_neg_inf(literal))
    {
      s.opt = kOptConstNegInf;
      s.literal = opt_name(kOptConstNegInf);
    }

    // 通过字符串判断类型

    size_t st = static_cast<size_t>(my::type_of_string(literal));
    if (st == kStrTypeErr)
    {
      mysym_invalid_symbol_format_exception("invalid symbol literal format = %s", literal.c_str());
    }
    else if ((st == kStrTypeInt) || (st == kStrTypeReal))
    {
      s.opt = kOptNumber;
      s.literal = literal;
    }
    else if (st == kStrTypeVar)
    {
      s.opt = kOptVariate;
      s.literal = literal;
    }

    return s;
  }
} // namespace mysym