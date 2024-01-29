#include <mysym/mysym.h>

namespace mysym
{
  static symbol_t __lor_num_num(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_num_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_log_log(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_func_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_sym_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_add_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static symbol_t __lor_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptOr, x, y);
  }

  static bool __lor_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __lor_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  symbol_t lor(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptOr, x, y);
  }

  void register_lor_rule()
  {
    // 数值 + xxx
    register_case(kOptOr, make_optsign(kOptNumber, kOptNumber), __lor_num_num);
    register_case(kOptOr, make_optsign(kOptNumber, kOptFrac), __lor_num_frac);
    register_case(kOptOr, make_optsign(kOptNumber, "nature"), __lor_num_nature);
    register_case(kOptOr, make_optsign(kOptNumber, kOptVariate), __lor_num_var);
    register_case(kOptOr, make_optsign(kOptNumber, "func"), __lor_num_func);

    // 分数 + xxx
    register_case(kOptOr, make_optsign(kOptFrac, kOptFrac), __lor_frac_frac);
    register_case(kOptOr, make_optsign(kOptFrac, "nature"), __lor_frac_nature);
    register_case(kOptOr, make_optsign(kOptFrac, kOptVariate), __lor_frac_var);
    register_case(kOptOr, make_optsign(kOptFrac, "func"), __lor_frac_func);

    // 常数 + xxx
    register_case(kOptOr, make_optsign("nature", "nature"), __lor_nature_nature);
    register_case(kOptOr, make_optsign("nature", kOptVariate), __lor_nature_var);
    register_case(kOptOr, make_optsign("nature", "func"), __lor_nature_func);

    // 变量 + xxx
    register_case(kOptOr, make_optsign(kOptVariate, kOptVariate), __lor_var_var);
    register_case(kOptOr, make_optsign(kOptVariate, "func"), __lor_var_func);

    // 特别函数
    register_case(kOptOr, make_optsign(kOptPow, kOptPow), __lor_pow_pow);
    register_case(kOptOr, make_optsign(kOptLog, kOptLog), __lor_log_log);

    // 函数 + xxx
    register_case(kOptOr, make_optsign("func", "func"), __lor_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptOr, make_optsign("sym", kOptMul), __lor_sym_mul);
    register_case(kOptOr, make_optsign("sym", kOptOr), __lor_sym_add);

    // 多项式 与 单项式
    register_case(kOptOr, make_optsign(kOptMul, kOptMul), __lor_mul_mul);
    register_case(kOptOr, make_optsign(kOptOr, kOptOr), __lor_add_add);
    register_case(kOptOr, make_optsign(kOptMul, kOptOr), __lor_mul_add);

    // 预处理与后置处理
    register_preprocess(kOptOr, __lor_preprocess);
    register_postprocess(kOptOr, __lor_postprocess);
  }
} // namespace mysym