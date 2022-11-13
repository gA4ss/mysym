#include <mysym/mysym.h>

namespace mysym
{

  library_ptr_t __plibrary = nullptr;

  library_ptr_t init_library()
  {
    library_ptr_t ptr = plibrary();
    ptr = std::make_shared<library_t>();
    return ptr;
  }

#define __insert_library_opt(opt, n) \
  {                                  \
    strings.push_back(n);            \
    names[opt] = strings.size() - 1; \
  }
  __library_t::__library_t()
  {
    __insert_library_opt(kOptNone, "none");
    __insert_library_opt(kOptAdd, "+");
    __insert_library_opt(kOptSub, "-");
    __insert_library_opt(kOptMul, "*");
    __insert_library_opt(kOptDiv, "/");
    __insert_library_opt(kOptMod, "%");
    __insert_library_opt(kOptSqrt, "sqrt");
    __insert_library_opt(kOptExp, "exp");
    __insert_library_opt(kOptLog, "log");
    __insert_library_opt(kOptFrac, "frac");
    __insert_library_opt(kOptSqrt, "sqrt");
    __insert_library_opt(kOptSin, "sin");
    __insert_library_opt(kOptCos, "cos");
    __insert_library_opt(kOptTan, "tan");
    __insert_library_opt(kOptCot, "cot");
    __insert_library_opt(kOptSec, "sec");
    __insert_library_opt(kOptCsc, "csc");
    __insert_library_opt(kOptArcSin, "asin");
    __insert_library_opt(kOptArcCos, "acos");
    __insert_library_opt(kOptArcTan, "atan");
    __insert_library_opt(kOptArcCot, "acot");
    __insert_library_opt(kOptArcSec, "asec");
    __insert_library_opt(kOptArcCsc, "acsc");
    __insert_library_opt(kOptSinh, "sinh");
    __insert_library_opt(kOptCosh, "cosh");
    __insert_library_opt(kOptTanh, "tanh");
    __insert_library_opt(kOptCoth, "coth");
    __insert_library_opt(kOptSech, "sech");
    __insert_library_opt(kOptCsch, "csch");
    __insert_library_opt(kOptArcSinh, "asinh");
    __insert_library_opt(kOptArcCosh, "acosh");
    __insert_library_opt(kOptArcTanh, "atanh");
    __insert_library_opt(kOptArcCoth, "acoth");
    __insert_library_opt(kOptArcSech, "asech");
    __insert_library_opt(kOptArcCsch, "acsch");
    __insert_library_opt(kOptConstE, "e");
    __insert_library_opt(kOptConstPI, "pi");
  }

  std::string __library_t::find(const symbol_ptr_t &ptr)
  {
    std::string name;
    if (names.find(ptr->opt) != names.end())
      name = strings[names[ptr->opt]];
    else
      name = ptr->name;
    return name;
  }

} // namespace mysym