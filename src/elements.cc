#include <mysym/mysym.h>
#include <functional>

namespace mysym
{

// #define is_add(o) (o == kOptAdd)
// #define is_sub(o) (o == kOptSub)
// #define is_mul(o) (o == kOptMul)
// #define is_div(o) (o == kOptDiv)
// #define is_pow(o) (o == kOptPow)
// #define is_log(o) (o == kOptLog)
// #define is_fact(o) (o == kOptFact)
// #define is_abs(o) (o == kOptAbs)
// #define is_mod(o) (o == kOptMod)
// #define is_var(o) (o == kOptVariate)
// #define is_num(o) (o == kOptNumber)
// #define is_int(o) is_num(o)
// #define is_flt(o) is_num(o)
// #define is_frac(o) (o == kOptFrac)

  static list_t __extract_elements(const symbol_t &s, std::function<bool(const symbol_t&)> f)
  {
    list_t l;
    if (is_single(s))
    {
      if (f(s))
        append(l, s, true);
    }
    else
    {
      for (auto it = s.items.begin(); it != s.items.end(); it++)
      {
        if (!is_single(s))
        {
          append(l, __extract_elements(*it, f), true);
        }
        else
        {
          if (f(*it))
            append(l, *it, true);
        }
      }
    }
    return l;
  }

  list_t variables(const symbol_t &s)
  {
    return __extract_elements(s, [](const symbol_t &x) -> bool 
      {return is_var(kind(x));});
  }

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
    list_t l;
    return l;
  }

  list_t natures(const symbol_t &s)
  {
    list_t l;
    return l;
  }

  list_t functions(const symbol_t &s)
  {
    list_t l;
    return l;
  }
} // namespace mysym