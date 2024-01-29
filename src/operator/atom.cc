#include <mysym/mysym.h>

namespace mysym
{

  static symbol_t __atom(const symbol_t &x)
  {
    return x;
  }

  void register_atom_rule()
  {
    // register_case(kOptVariate, __atom);
    // register_case(kOptNumber, __atom);
    // register_case(kOptFrac, __atom);
    // register_case(kOptConstE, __atom);
    // register_case(kOptConstPI, __atom);
    // register_case(kOptConstInf, __atom);
    // register_case(kOptConstNegInf, __atom);
  }
} // namespace mysym