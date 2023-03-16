#include <mysym/mysym.h>

namespace mysym
{
  void init()
  {
    init_symopt();
    init_symset();
    init_global();
    init_rule();
    plibrary() = init_library();
  }
} // namespace mysym