#ifndef MYSYM_CONSTRUCT_H_
#define MYSYM_CONSTRUCT_H_

#include <mysym/mysym.h>

namespace mysym
{

//
// 运算符号
//
#define c_add(s1, s2) make(kOptAdd, s1, s2, false)
#define c_mul(s1, s2) make(kOptMul, s1, s2, false)
#define c_equ(s1, s2) make(kOptEqu, s1, s2, false)
#define c_neq(s1, s2) make(kOptNotEqu, s1, s2, false)
#define c_lt(s1, s2) make(kOptLT, s1, s2, false)
#define c_le(s1, s2) make(kOptLE, s1, s2, false)
#define c_gt(s1, s2) make(kOptGT, s1, s2, false)
#define c_ge(s1, s2) make(kOptGE, s1, s2, false)
#define c_cmp(s1, s2) make(kOptCmp, s1, s2, false)
#define c_pow(s1, s2) make(kOptPow, s1, s2, false)
#define c_log(s1, s2) make(kOptLog, s1, s2, false)
#define c_fact(s1, s2) make(kOptFact, s1, s2, false)
#define c_abs(s) make(kOptAbs, s, false)
#define c_mod(s1, s2) make(kOptMod, s1, s2, false)
#define c_sin(s) make(kOptSin, s, false)
#define c_cos(s) make(kOptCos, s, false)
#define c_tan(s) make(kOptTan, s, false)
#define c_cot(s) make(kOptCot, s, false)
#define c_sec(s) make(kOptSec, s, false)
#define c_csc(s) make(kOptCsc, s, false)
#define c_asin(s) make(kOptArcSin, s, false)
#define c_acos(s) make(kOptArcCos, s, false)
#define c_atan(s) make(kOptArcTan, s, false)
#define c_acot(s) make(kOptArcCot, s, false)
#define c_asec(s) make(kOptArcSec, s, false)
#define c_acsc(s) make(kOptArcCsc, s, false)
#define c_sinh(s) make(kOptSinh, s, false)
#define c_cosh(s) make(kOptCosh, s, false)
#define c_tanh(s) make(kOptTanh, s, false)
#define c_coth(s) make(kOptCoth, s, false)
#define c_sech(s) make(kOptSech, s, false)
#define c_csch(s) make(kOptCsch, s, false)
#define c_asinh(s) make(kOptArcSinh, s, false)
#define c_acosh(s) make(kOptArcCosh, s, false)
#define c_atanh(s) make(kOptArcTanh, s, false)
#define c_acoth(s) make(kOptArcCoth, s, false)
#define c_asech(s) make(kOptArcSech, s, false)
#define c_acsch(s) make(kOptArcCsch, s, false)
#define c_frac(s1, s2) make(kOptFrac, s1, s2, false)

//
// 扩展运算符
//
#define c_minus(s) c_mul(create_int("-1"), s)
#define c_sub(s1, s2) make(kOptAdd, s1, c_mul(create_int("-1"), s2), false)
#define c_div(s1, s2) make(kOptMul, s1, c_pow(s2, create_int("-1")), false)
#define c_sqrt(s) make(kOptPow, s, create_frac("1", "2"), false)

} // namespace mysym

#endif // MYSYM_CONSTRUCT_H_