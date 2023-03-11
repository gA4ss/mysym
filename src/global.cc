#include <mysym/mysym.h>

namespace mysym
{
  int_t gConstZero;
  int_t gConstOne;
  int_t gConstNegOne;
  flt_t gConstE;
  flt_t gConstPI;
  flt_t gConstInf;
  flt_t gConstNegInf;
  symbol_t gConstUDF;

  void init_global()
  {
    gConstZero = create_int("0");
    gConstOne = create_int("1");
    gConstNegOne = create_int("-1");
    gConstE = create_opt(kOptConstE);
    gConstPI = create_opt(kOptConstPI);
    gConstInf = create_opt(kOptConstInf);
    gConstNegInf = create_opt(kOptConstNegInf);
    gConstUDF = create_opt(kOptNone);
  }
} // namespace mysym