#include <mysym/mysym.h>
#include "__misc.h"
#include <mysym/construct.h>

namespace mysym
{
  int_t gConstZero;
  int_t gConstOne;
  int_t gConstNegOne;
  flt_t gConstE;
  flt_t gConstPI;
  flt_t gConstHalfPI;
  flt_t gConstDoublePI;
  flt_t gConstInf;
  flt_t gConstNegInf;
  symbol_t gConstUDF;
  std::vector<std::string> gSymOpts;
  std::vector<std::string> gOptSets;

  static void __init_consts()
  {
    gConstZero = create_int("0");
    gConstOne = create_int("1");
    gConstNegOne = create_int("-1");
    gConstE = create_opt(kOptConstE);
    gConstPI = create_opt(kOptConstPI);
    gConstHalfPI = just_make2(kOptMul, c_frac(gConstOne, create_int("2")), gConstPI);
    gConstDoublePI = just_make2(kOptMul, create_int("2"), gConstPI);
    gConstInf = create_opt(kOptConstInf);
    gConstNegInf = create_opt(kOptConstNegInf);
    gConstUDF = create_opt(kOptNone);
  }

  static void __init_symopts()
  {
    std::string s1 = symopts();
    std::string s2 = optsets();
    gSymOpts = split_string(s1);
    gOptSets = split_string(s2);
  }

  void init_global()
  {
    __init_consts();
    __init_symopts();
  }
} // namespace mysym