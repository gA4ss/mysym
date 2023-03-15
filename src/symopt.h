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
    kOptFloat,
    kOptFrac,
    kOptConstE,
    kOptConstPI,
    kOptConstInf,
    kOptConstNegInf,
    kOptMax
  } opt_t;
#define kOptNameMax kOptVariate

#define is_none(o) (o == kOptNone)
#define is_und(o) is_none(o)
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
#define is_2ps_func(o) ((o == kOptPow) || (o == kOptLog) || (o == kOptMod))
#define is_sym(o) (o >= kOptVariate)
#define is_var(o) (o == kOptVariate)
#define is_const(o) (o >= kOptInteger)
#define is_int(o) (o == kOptInteger)
#define is_flt(o) (o == kOptFloat)
#define is_num(o) (is_int(o) || is_flt(o))
#define is_nature(o) ((o == kOptConstE) || (o == kOptConstPI) || (o == kOptConstInf) || \
                      (o == kOptConstNegInf))
#define is_frac(o) (o == kOptFrac)
#define is_e(o) (o == kOptConstE)
#define is_pi(o) (o == kOptConstPI)
#define is_inf(o) (o == kOptConstInf)
#define is_neg_inf(o) (o == kOptConstNegInf)

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
// kOptNameMax
#define opt_name(o) (((o >= kOptNone) && (o < kOptMax)) ? __operator[o].name : "")
#define opt_prio(o) (((o >= kOptNone) && (o < kOptMax)) ? __operator[o].prio : -1)
#define opt_asso(o) (((o >= kOptNone) && (o < kOptMax)) ? __operator[o].asso : -1)

  typedef struct __symopt_t
  {
    operator_t opt;
  } symopt_t;

  typedef struct __optset_t
  {
    std::string name;
    std::map<std::string, symopt_t> items;
  } optset_t;

  typedef std::vector<std::string> optnames_t;

  optset_t create(std::string setname, std::string optnames);
  optset_t create(std::string setname, optnames_t optnames);
  optset_t create_from_set(std::string setname, std::vector<std::string> setnames);
  bool in_set(std::string setname, std::string optname);
  optnames_t in_set(std::string setname, optnames_t optnames);
  std::string symopts();

} // namespace mysym

#endif // MYSYM_SYMOPT_H_