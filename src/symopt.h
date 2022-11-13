#ifndef MYSYM_SYMOPT_H_
#define MYSYM_SYMOPT_H_

namespace mysym
{

  typedef enum
  {
    kOptNone,
    kOptAdd,
    kOptSub,
    kOptMul,
    kOptDiv,
    kOptMod,
    kOptSqrt,
    kOptExp,
    kOptLog,
    kOptFrac,
    kOptSin,
    kOptCos,
    kOptTan,
    kOptCot,
    kOptSec,
    kOptCsc,
    kOptArcSin,
    kOptArcCos,
    kOptArcTan,
    kOptArcCot,
    kOptArcSec,
    kOptArcCsc,
    kOptSinh,
    kOptCosh,
    kOptTanh,
    kOptCoth,
    kOptSech,
    kOptCsch,
    kOptArcSinh,
    kOptArcCosh,
    kOptArcTanh,
    kOptArcCoth,
    kOptArcSech,
    kOptArcCsch,
    kOptConstE,
    kOptConstPI,
    kOptConst = 0x1000,
    kOptVar = 0x2000,
    kOptFunc = 0x3000
  } opt_t;

#define is_opt_none(o) (o == kOptNone)
#define is_opt(o) ((o > kOptNone) && (o <= kOptConstPI))
#define is_operator(o) ((o >= kOptAdd) && (o <= kOptMod))
#define is_const(o) ((o == kOptConstE) || (o == kOptConstPI) || ((o > kOptConst) && (o < kOptVar)))
#define is_var(o) ((o > kOptVar) && (o < kOptFunc))
#define is_func(o) ((o > kOptFunc) || ((o >= kOptSqrt) && (o <= kOptArcCsch)))
#define is_elm_func(o) ((o == kOptExp) || (o == kOptLog) || (o == kOptFrac))

} // namespace mysym

#endif // MYSYM_SYMOPT_H_