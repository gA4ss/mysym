#include <mysym/mysym.h>

namespace mysym
{
  static symbol_t __ge_num_num(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_num_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_log_log(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_func_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_sym_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_add_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static symbol_t __ge_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGE, x, y);
  }

  static bool __ge_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __ge_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  symbol_t ge(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptGE, x, y);
  }

  void register_ge_rule()
  {
    // 数值 + xxx
    register_case(kOptGE, make_optsign(kOptNumber, kOptNumber), __ge_num_num);
    register_case(kOptGE, make_optsign(kOptNumber, kOptFrac), __ge_num_frac);
    register_case(kOptGE, make_optsign(kOptNumber, "nature"), __ge_num_nature);
    register_case(kOptGE, make_optsign(kOptNumber, kOptVariate), __ge_num_var);
    register_case(kOptGE, make_optsign(kOptNumber, "func"), __ge_num_func);

    // 分数 + xxx
    register_case(kOptGE, make_optsign(kOptFrac, kOptFrac), __ge_frac_frac);
    register_case(kOptGE, make_optsign(kOptFrac, "nature"), __ge_frac_nature);
    register_case(kOptGE, make_optsign(kOptFrac, kOptVariate), __ge_frac_var);
    register_case(kOptGE, make_optsign(kOptFrac, "func"), __ge_frac_func);

    // 常数 + xxx
    register_case(kOptGE, make_optsign("nature", "nature"), __ge_nature_nature);
    register_case(kOptGE, make_optsign("nature", kOptVariate), __ge_nature_var);
    register_case(kOptGE, make_optsign("nature", "func"), __ge_nature_func);

    // 变量 + xxx
    register_case(kOptGE, make_optsign(kOptVariate, kOptVariate), __ge_var_var);
    register_case(kOptGE, make_optsign(kOptVariate, "func"), __ge_var_func);

    // 特别函数
    register_case(kOptGE, make_optsign(kOptPow, kOptPow), __ge_pow_pow);
    register_case(kOptGE, make_optsign(kOptLog, kOptLog), __ge_log_log);

    // 函数 + xxx
    register_case(kOptGE, make_optsign("func", "func"), __ge_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptGE, make_optsign("sym", kOptMul), __ge_sym_mul);
    register_case(kOptGE, make_optsign("sym", kOptGE), __ge_sym_add);

    // 多项式 与 单项式
    register_case(kOptGE, make_optsign(kOptMul, kOptMul), __ge_mul_mul);
    register_case(kOptGE, make_optsign(kOptGE, kOptGE), __ge_add_add);
    register_case(kOptGE, make_optsign(kOptMul, kOptGE), __ge_mul_add);

    // 预处理与后置处理
    register_preprocess(kOptGE, __ge_preprocess);
    register_postprocess(kOptGE, __ge_postprocess);
  }
} // namespace mysym