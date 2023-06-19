#include <mysym/mysym.h>

namespace mysym
{
  typedef bool (*fptr_filter_found_t)(const symbol_t &);
  static list_t __filter(const symbol_t &s, fptr_filter_found_t fptr, bool recursion = false)
  {
    list_t l;
    if (is_single(s) && fptr(s))
    {
      append(l, s);
    }
    else
    {
      if (recursion)
      {
        for (auto it : s.items)
        {
          if (!is_single(it))
          {
            append(l, __filter(it, fptr));
          }
          else
          {
            if (fptr(it))
              append(l, it);
          }
        }/* end for */
      }
    }
    return l;
  }

  static bool __is_variable(const symbol_t &s)
  {
    return is_var(kind(s));
  }
  list_t variables(const symbol_t &s, bool recursion = false)
  {
    return __filter(s, __is_variable, recursion);
  }

  static bool __is_constant(const symbol_t &s)
  {
    return is_const(kind(s));
  }
  list_t constants(const symbol_t &s, bool recursion = false)
  {
    return __filter(s, __is_constant, recursion);
  }

  static bool __is_integer(const symbol_t &s)
  {
    return is_num(kind(s)) && (my::type_of_string(s.literal) == kStrTypeInt) ?
            true : false;
  }
  list_t integers(const symbol_t &s, bool recursion = false)
  {
    return __filter(s, __is_integer, recursion);
  }

  static bool __is_real(const symbol_t &s)
  {
    return is_num(kind(s)) && (my::type_of_string(s.literal) == kStrTypeReal) ?
            true : false;
  }
  list_t reals(const symbol_t &s, bool recursion = false)
  {
    return __filter(s, __is_real, recursion);
  }

  static bool __is_fraction(const symbol_t &s)
  {
    return is_frac(kind(s));
  }
  list_t fractions(const symbol_t &s, bool recursion = false)
  {
    return __filter(s, __is_fraction, recursion);
  }

  static bool __is_nature(const symbol_t &s)
  {
    return is_nature(kind(s));
  }
  list_t natures(const symbol_t &s, bool recursion = false)
  {
    return __filter(s, __is_nature, recursion);
  }

  static bool __is_func(const symbol_t &s)
  {
    return is_func(kind(s));
  }
  list_t functions(const symbol_t &s, bool recursion = false)
  {
    return __filter(s, __is_func, recursion);
  }
} // namespace mysym