#include <mysym/mysym.h>

namespace mysym
{

  void init()
  {
    plibrary() = init_library();
  }

  __symbol_t::__symbol_t()
  {
    opt = kOptNone;
  }

  void append(symbol_t& y, const symbol_t &x)
  {
    y.items.push_back(x);
  }
} // namespace mysym