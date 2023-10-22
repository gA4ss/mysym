#include <mysym/mysym.h>

namespace mysym
{
  __symbol_t::__symbol_t()
  {
    opt = kOptNone;
  }

  __symbol_t& __symbol_t::operator[](size_t i)
  {
    if (i >= items.size())
    {
      mysym_param_is_out_of_range_exception("i = %lu, size of items = %lu", 
                                            i, items.size());
    }
    return items[i];
  }

  size_t size(const symbol_t &s)
  {
    return size(s.items);
  }

  void append(symbol_t& y, const symbol_t &x)
  {
    y.items.push_back(x);
  }

  void append(symbol_t& y, const symbol_items_t &x)
  {
    append(y.items, x);
  }

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