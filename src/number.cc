#include <mysym/mysym.h>
#include <mynum/wrapper.h>

namespace mysym
{
  symbol_t number_to_symbol(const number_t &f)
  {
    return create_flt(f.value());
  }

  number_t symbol_to_number(const symbol_t &s)
  {
    return is_num(kind(s)) ? number_t(s.literal) : number_t(0);
  }
} // namespace mysym