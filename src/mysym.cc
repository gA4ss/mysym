#include <mysym/mysym.h>

namespace mysym
{
  bool symbol_is_integer(const num_t &x)
  {
    if (!is_num(kind(x)))
      return false;
    return my::type_of_string(x.literal) == kStrTypeInt;
  }

  bool symbol_is_real(const num_t &x)
  {
    if (!is_num(kind(x)))
      return false;
    return my::type_of_string(x.literal) == kStrTypeReal;
  }
} // namespace mysym