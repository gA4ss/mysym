#include <mysym/mysym.h>
#include <functional>

namespace mysym
{

  static list_t __extract_elements(const symbol_t &s, std::function<bool(const symbol_t&)> f)
  {
    list_t l;
    if (f(s))
    {
      append(l, s, true);
    }

    if (!is_single(s))
    {
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
        append(l, __extract_elements(*it, f), true);
      }
    }
    return l;
  }

  list_t variables(const symbol_t &s)
  {
    return __extract_elements(s, [](const symbol_t &x) -> bool 
      {return is_var(kind(x));});
  }

  //
  // 将单个变量，函数，单项式判断作为变量
  //
  list_t abstract_variables(const symbol_t &s)
  {
    list_t l;
    if (is_single(s))
    {
      if (is_var(kind(s)) || is_func(kind(s)))
        append(l, s, true);
    }
    else
    {
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
        if (is_add(kind(*it)))
        {
          append(l, abstract_variables(*it), true);
        }
        else if (is_mul(kind(*it)))
        {
          append(l, *it, true);
          append(l, abstract_variables(*it), true);
        }
        else
        {
          if (is_var(kind(*it)) || is_func(kind(*it)))
            append(l, *it, true);
        }
      }
    }
    return l;
  }

  list_t constants(const symbol_t &s)
  {
    return __extract_elements(s, [](const symbol_t &x) -> bool 
      {return is_const(kind(x));});
  }

  list_t integers(const symbol_t &s)
  {
    return __extract_elements(s, [](const symbol_t &x) -> bool 
      {return (is_int(kind(x)) && symbol_is_integer(x));});
  }

  list_t reals(const symbol_t &s)
  {
    return __extract_elements(s, [](const symbol_t &x) -> bool 
      {return (is_flt(kind(x)) && symbol_is_real(x));});
  }

  list_t fractions(const symbol_t &s)
  {
    return __extract_elements(s, [](const symbol_t &x) -> bool 
      {return is_frac(kind(x));});
  }

  list_t natures(const symbol_t &s)
  {
    return __extract_elements(s, [](const symbol_t &x) -> bool 
      {return is_nature(kind(x));});
  }

  list_t functions(const symbol_t &s)
  {
    return __extract_elements(s, [](const symbol_t &x) -> bool 
      {return is_func(kind(x));});
  }

  list_t pows(const symbol_t &s)
  {
    return __extract_elements(s, [](const symbol_t &x) -> bool 
      {return is_pow(kind(x));});
  }

  list_t logs(const symbol_t &s)
  {
    return __extract_elements(s, [](const symbol_t &x) -> bool 
      {return is_log(kind(x));});
  }

  list_t abses(const symbol_t &s)
  {
    return __extract_elements(s, [](const symbol_t &x) -> bool 
      {return is_abs(kind(x));});
  }
} // namespace mysym