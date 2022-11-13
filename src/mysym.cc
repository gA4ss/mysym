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

  void __symbol_t::link(std::shared_ptr<__symbol_t> s)
  {
    next.push_back(s);
  }

  bool __symbol_t::earse(std::shared_ptr<__symbol_t> s)
  {
    symbol_link_iter_t it = std::find(next.begin(), next.end(), s);
    if (it != next.end())
    {
      next.erase(it);
      return true;
    }
    return false;
  }
} // namespace mysym