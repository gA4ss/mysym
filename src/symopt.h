#ifndef MYSYM_SYMOPT_H_
#define MYSYM_SYMOPT_H_

namespace mysym
{

  typedef enum
  {
    //
    // 表明操作为空
    //
    kOptNone,

    //
    // 基础运算符
    //
    kOptAdd,
    kOptSub,
    kOptMul,
    kOptDiv,
    kOptMod,

    //
    // 基础函数
    //
    kOptAbs,
    kOptSqrt,
    kOptPow,
    kOptLog,
    kOptFact,
    kOptFrac,

    //
    // 三角函数
    //
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

    //
    // 双曲函数
    //
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

    //
    // 符号类型
    // 包含了，变量，常量等等都算是符号
    //
    kOptSymbol,
    kOptInteger,
    kOptReal
  } opt_t;
#define kOptMax kOptSymbol

#define is_none(o) (o == kOptNone)
#define is_opt(o) ((o > kOptNone) && (o < kOptSymbol))
#define is_basic(o) ((o >= kOptAdd) && (o <= kOptMod))
#define is_sym(o) (o >= kOptSymbol)
#define is_var(o) (o == kOptSymbol)
#define is_num(o) ((o == kOptInteger) || (o == kOptReal))
#define is_int(o) (o == kOptInteger)
#define is_real(o) (o == kOptReal)
#define is_func(o) ((o > kOptMod) && (o < kOptSymbol))

  typedef struct __operator_t
  {
    opt_t opt;
    std::string name;
    int prio;
    int asso;
  } operator_t;

  typedef enum
  {
    kAssoLeft,
    kAssoRight
  } asso_t;

  extern operator_t __operator[kOptMax];
#define opt_name(o) (((o >= kOptNone) && (o < kOptMax)) ? __operator[o].name : "")
#define opt_prio(o) (((o >= kOptNone) && (o < kOptMax)) ? __operator[o].prio : -1)
#define opt_asso(o) (((o >= kOptNone) && (o < kOptMax)) ? __operator[o].asso : -1)

} // namespace mysym

#endif // MYSYM_SYMOPT_H_