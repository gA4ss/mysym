#include <mysym/mysym.h>

namespace mysym
{

  symbol_ptr_t create(opt_t opt, std::string name)
  {
    symbol_ptr_t ptr = make_symbol_ptr();
    ptr->opt = opt;
    
    if (is_opt(opt))
    {
      ptr->name = plibrary()->strings[plibrary()->names[opt]];
    }
    else
    {
      ptr->name = name;
    }
    return ptr;
  }
} // namespace mysym