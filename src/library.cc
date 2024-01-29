#include <mysym/mysym.h>

namespace mysym
{

  library_ptr_t __plibrary = nullptr;

  __library_t::__library_t()
  {
    config.is_compute_frac_float = false;
    config.is_mul_polynomial_not_expand = false;
  }

  library_ptr_t init_library()
  {
    library_ptr_t ptr = plibrary();
    ptr = std::make_shared<library_t>();
    return ptr;
  }

} // namespace mysym