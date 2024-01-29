#include <mysym/mysym.h>

namespace mysym
{
  static std::unordered_map<opt_t, fptr_single_execute_t> __single_operators;
  static std::unordered_map<opt_t, fptr_execute_t> __operators;

  symbol_t call_operator(opt_t opt, const symbol_t &x)
  {
    if (__single_operators.find(opt) == __single_operators.end())
      return gConstUDF;
    return __single_operators[opt](x);
  }

  symbol_t call_operator(opt_t opt, const symbol_t &x, const symbol_t &y)
  {
    if (__operators.find(opt) == __operators.end())
      return gConstUDF;
    return __operators[opt](x, y);
  }

  fptr_single_operator_t get_single_operator(opt_t opt)
  {
    fptr_single_operator_t fptr = nullptr;
    if (__single_operators.find(opt) != __single_operators.end())
      fptr = __single_operators[opt];
    return fptr;
  }

  fptr_operator_t get_operator(opt_t opt)
  {
    fptr_operator_t fptr = nullptr;
    if (__operators.find(opt) != __operators.end())
      fptr = __operators[opt];
    return fptr;
  }

  void init_operator()
  {
    //
    // 双目运算符
    //
    __operators[kOptAdd] = add;
    __operators[kOptSub] = sub;
    __operators[kOptMul] = mul;
    __operators[kOptDiv] = div;
    __operators[kOptMod] = mod;

    __operators[kOptPow] = pow;
    __operators[kOptLog] = log;

    __operators[kOptFrac] = frac;

    __operators[kOptAnd] = land;
    __operators[kOptOr] = lor;

    __operators[kOptEqu] = equ;
    __operators[kOptNotEqu] = neq;
    __operators[kOptLT] = lt;
    __operators[kOptLE] = le;
    __operators[kOptGT] = gt;
    __operators[kOptGE] = ge;

    __operators[kOptCmp] = cmp;

    //
    // 单目运算符
    //
    __single_operators[kOptAbs] = abs;
    __single_operators[kOptFact] = fact;
    __single_operators[kOptNot] = lnot;

    __single_operators[kOptSin] = sin;
    __single_operators[kOptCos] = cos;
    __single_operators[kOptTan] = tan;
    __single_operators[kOptCot] = cot;
    __single_operators[kOptSec] = sec;
    __single_operators[kOptCsc] = csc;

    __single_operators[kOptArcSin] = arcsin;
    __single_operators[kOptArcCos] = arccos;
    __single_operators[kOptArcTan] = arctan;
    __single_operators[kOptArcCot] = arccot;
    __single_operators[kOptArcSec] = arcsec;
    __single_operators[kOptArcCsc] = arccsc;

    __single_operators[kOptSinh] = sinh;
    __single_operators[kOptCosh] = cosh;
    __single_operators[kOptTanh] = tanh;
    __single_operators[kOptCoth] = coth;
    __single_operators[kOptSech] = sech;
    __single_operators[kOptCsch] = csch;

    __single_operators[kOptArcSinh] = arcsinh;
    __single_operators[kOptArcCosh] = arccosh;
    __single_operators[kOptArcTanh] = arctanh;
    __single_operators[kOptArcCoth] = arccoth;
    __single_operators[kOptArcSech] = arcsech;
    __single_operators[kOptArcCsch] = arccsch;
  }

} // namespace mysym