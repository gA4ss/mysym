#include <mysym/mysym.h>

namespace mysym
{
  symbol_t iterate(fptr_iteration_t fptr, const list_t &s)
  {
    size_t n = size(s);
    symbol_t k = s[0];
    for (size_t i = 1; i < n; i++)
    {
      k = fptr(k, s[i]);
    }
    return k;
  }

  symbol_t iterate(opt_t opt, const list_t &s)
  {
    size_t n = size(s);
    symbol_t k = s[0];
    for (size_t i = 1; i < n; i++)
    {
      k = call_operator(opt, k, s[i]);
    }
    return k;
  }
} // namespace mysym