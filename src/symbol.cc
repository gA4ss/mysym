#include <mysym/mysym.h>

namespace mysym
{
  __symbol_t::__symbol_t()
  {
    opt = kOptNone;
  }

  __symbol_t &__symbol_t::operator[](size_t i)
  {
    if (i >= items.size())
    {
      mysym_param_is_out_of_range_exception("i = %lu, size of items = %lu",
                                            i, items.size());
    }
    return items[i];
  }

  const __symbol_t &__symbol_t::operator[](size_t i) const
  {
    if (i >= items.size())
    {
      mysym_param_is_out_of_range_exception("i = %lu, size of items = %lu",
                                            i, items.size());
    }
    return items[i];
  }

  void __symbol_t::operator=(const __symbol_t &x)
  {
    opt = x.opt;
    literal = x.literal;
    items = x.items;

#ifdef DEBUG
    dbgstr = print_string(x);
#endif
  }

  size_t size(const symbol_t &s)
  {
    return size(s.items);
  }

  void append(symbol_t &y, const symbol_t &x)
  {
    y.items.push_back(x);
  }

  void append(symbol_t &y, const symbol_items_t &x)
  {
    append(y.items, x);
  }

  void append(symbol_t &y, const symbol_t &x, size_t s, size_t e)
  {
    if ((s >= size(y)) || (s > e))
    {
      mysym_param_is_out_of_range_exception("s = %lu, e = %lu",
                                            s, e);
    }

    if (e == static_cast<size_t>(-1))
      y.items.insert(y.items.end(), x.items.begin() + s, x.items.end());
    else
      y.items.insert(y.items.end(), x.items.begin() + s, x.items.begin() + e);
  }

  symbol_t at(const symbol_t &x, size_t i)
  {
    return x[i];
  }

  symbol_items_t items(const symbol_t &x)
  {
    return x.items;
  }

  symbol_t erase(symbol_t &x, size_t i)
  {
    if (i >= x.items.size())
    {
      mysym_param_is_out_of_range_exception("i = %lu, size of items = %lu",
                                            i, x.items.size());
    }
    symbol_t e = x[i];
    x.items.erase(x.items.begin() + i);

    // 如果x只剩下1个元素，则进行顶替。
    if (x.items.size() == 1)
    {
      x.opt = x.items[0].opt;
      x.literal = x.items[0].literal;
#ifdef DEBUG
      x.dbgstr = print_string(x.items[0]);
#endif
      x.items.clear();
    }

    return e;
  }
} // namespace mysym