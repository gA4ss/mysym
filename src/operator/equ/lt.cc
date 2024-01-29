#include <mysym/mysym.h>

namespace mysym
{
  static symbol_t __lt_num_num(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_num_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_log_log(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_func_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_sym_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_add_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static symbol_t __lt_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLT, x, y);
  }

  static bool __lt_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __lt_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  symbol_t lt(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptLT, x, y);
  }

  void register_lt_rule()
  {
    // 数值 + xxx
    register_case(kOptLT, make_optsign(kOptNumber, kOptNumber), __lt_num_num);
    register_case(kOptLT, make_optsign(kOptNumber, kOptFrac), __lt_num_frac);
    register_case(kOptLT, make_optsign(kOptNumber, "nature"), __lt_num_nature);
    register_case(kOptLT, make_optsign(kOptNumber, kOptVariate), __lt_num_var);
    register_case(kOptLT, make_optsign(kOptNumber, "func"), __lt_num_func);

    // 分数 + xxx
    register_case(kOptLT, make_optsign(kOptFrac, kOptFrac), __lt_frac_frac);
    register_case(kOptLT, make_optsign(kOptFrac, "nature"), __lt_frac_nature);
    register_case(kOptLT, make_optsign(kOptFrac, kOptVariate), __lt_frac_var);
    register_case(kOptLT, make_optsign(kOptFrac, "func"), __lt_frac_func);

    // 常数 + xxx
    register_case(kOptLT, make_optsign("nature", "nature"), __lt_nature_nature);
    register_case(kOptLT, make_optsign("nature", kOptVariate), __lt_nature_var);
    register_case(kOptLT, make_optsign("nature", "func"), __lt_nature_func);

    // 变量 + xxx
    register_case(kOptLT, make_optsign(kOptVariate, kOptVariate), __lt_var_var);
    register_case(kOptLT, make_optsign(kOptVariate, "func"), __lt_var_func);

    // 特别函数
    register_case(kOptLT, make_optsign(kOptPow, kOptPow), __lt_pow_pow);
    register_case(kOptLT, make_optsign(kOptLog, kOptLog), __lt_log_log);

    // 函数 + xxx
    register_case(kOptLT, make_optsign("func", "func"), __lt_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptLT, make_optsign("sym", kOptMul), __lt_sym_mul);
    register_case(kOptLT, make_optsign("sym", kOptLT), __lt_sym_add);

    // 多项式 与 单项式
    register_case(kOptLT, make_optsign(kOptMul, kOptMul), __lt_mul_mul);
    register_case(kOptLT, make_optsign(kOptLT, kOptLT), __lt_add_add);
    register_case(kOptLT, make_optsign(kOptMul, kOptLT), __lt_mul_add);

    // 预处理与后置处理
    register_preprocess(kOptLT, __lt_preprocess);
    register_postprocess(kOptLT, __lt_postprocess);
  }
} // namespace mysym