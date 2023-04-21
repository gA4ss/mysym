#include <mysym/mysym.h>

namespace mysym
{
  void register_atom_rule()
  {
    append_entry(kOptVariate, default_entry);
    append_entry(kOptNumber, default_entry);
    append_entry(kOptFrac, default_entry);
    append_entry(kOptConstE, default_entry);
    append_entry(kOptConstPI, default_entry);
    append_entry(kOptConstInf, default_entry);
    append_entry(kOptConstNegInf, default_entry);
  }
} // namespace mysym