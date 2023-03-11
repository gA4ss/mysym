#include <mysym/mysym.h>

namespace mysym
{
  void init()
  {
    init_global();
    plibrary() = init_library();
  }
} // namespace mysym