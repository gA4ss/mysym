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
    // 在自动化简之后表达式解构中仅存在加法与乘法
    //
    kOptAdd,
    kOptMul,

    //
    // 指数函数
    //
    kOptPow,

    //
    // 基础函数
    //
    kOptLog,
    kOptFact,
    kOptAbs,
    kOptMod,

    //
    // 三角函数
    //
    kOptSin,
    kOptCos,
    kOptTan,
    kOptCot,
    kOptSec,
    kOptCsc,

    //
    // 反三角函数
    //
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

    //
    // 反双曲函数
    //
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
    kOptVariate,
    kOptInteger,
    kOptReal,
    kOptFrac,
    kOptMax
  } opt_t;
#define kOptNameMax kOptVariate

#define is_none(o) (o == kOptNone)
#define is_opt(o) ((o > kOptNone) && (o < kOptVariate))
#define is_add(o) (o == kOptAdd)
#define is_mul(o) (o == kOptMul)
#define is_basic(o) ((o == kOptAdd) || (o == kOptMul))
#define is_pow(o) (o == kOptPow)
#define is_log(o) (o == kOptLog)
#define is_fact(o) (o == kOptFact)
#define is_abs(o) (o == kOptAbs)
#define is_mod(o) (o == kOptMod)
#define is_basic_func(o) ((o >= kOptLog) && (o <= kOptMod))
#define is_trigo(o) ((o >= kOptSin) && (o <= kOptCsc))
#define is_inv_trigo(o) ((o >= kOptArcSin) && (o <= kOptArcCsc))
#define is_hyper(o) ((o >= kOptSinh) && (o <= kOptCsch))
#define is_inv_hyper(o) ((o >= kOptArcSinh) && (o <= kOptArcCsch))
#define is_func(o) ((o >= kOptPow) && (o <= kOptArcCsch))
#define is_sym(o) (o >= kOptVariate)
#define is_var(o) (o == kOptVariate)
#define is_num(o) ((o == kOptInteger) || (o == kOptReal))
#define is_int(o) (o == kOptInteger)
#define is_real(o) (o == kOptReal)
#define is_frac(o) (o == kOptFrac)
#define is_const(o) (o >= kOptInteger)

  typedef struct __operator_t
  {
    opt_t opt;
    std::string name;
    int prio;
    int asso;
  } operator_t;

  typedef enum
  {
    kAssoNone,
    kAssoLeft,
    kAssoRight
  } asso_t;

  extern operator_t __operator[kOptMax];
#define opt_name(o) (((o >= kOptNone) && (o < kOptNameMax)) ? __operator[o].name : "")
#define opt_prio(o) (((o >= kOptNone) && (o < kOptNameMax)) ? __operator[o].prio : -1)
#define opt_asso(o) (((o >= kOptNone) && (o < kOptNameMax)) ? __operator[o].asso : -1)

} // namespace mysym

#endif // MYSYM_SYMOPT_H_