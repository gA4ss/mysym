#include <mysym/mysym.h>

namespace mysym
{
  static symbol_t __land_num_num(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_num_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_log_log(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_func_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_sym_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_add_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static symbol_t __land_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptAnd, x, y);
  }

  static bool __land_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __land_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  symbol_t land(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptAnd, x, y);
  }

  void register_land_rule()
  {
    // 数值 + xxx
    register_case(kOptAnd, make_optsign(kOptNumber, kOptNumber), __land_num_num);
    register_case(kOptAnd, make_optsign(kOptNumber, kOptFrac), __land_num_frac);
    register_case(kOptAnd, make_optsign(kOptNumber, "nature"), __land_num_nature);
    register_case(kOptAnd, make_optsign(kOptNumber, kOptVariate), __land_num_var);
    register_case(kOptAnd, make_optsign(kOptNumber, "func"), __land_num_func);

    // 分数 + xxx
    register_case(kOptAnd, make_optsign(kOptFrac, kOptFrac), __land_frac_frac);
    register_case(kOptAnd, make_optsign(kOptFrac, "nature"), __land_frac_nature);
    register_case(kOptAnd, make_optsign(kOptFrac, kOptVariate), __land_frac_var);
    register_case(kOptAnd, make_optsign(kOptFrac, "func"), __land_frac_func);

    // 常数 + xxx
    register_case(kOptAnd, make_optsign("nature", "nature"), __land_nature_nature);
    register_case(kOptAnd, make_optsign("nature", kOptVariate), __land_nature_var);
    register_case(kOptAnd, make_optsign("nature", "func"), __land_nature_func);

    // 变量 + xxx
    register_case(kOptAnd, make_optsign(kOptVariate, kOptVariate), __land_var_var);
    register_case(kOptAnd, make_optsign(kOptVariate, "func"), __land_var_func);

    // 特别函数
    register_case(kOptAnd, make_optsign(kOptPow, kOptPow), __land_pow_pow);
    register_case(kOptAnd, make_optsign(kOptLog, kOptLog), __land_log_log);

    // 函数 + xxx
    register_case(kOptAnd, make_optsign("func", "func"), __land_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptAnd, make_optsign("sym", kOptMul), __land_sym_mul);
    register_case(kOptAnd, make_optsign("sym", kOptAnd), __land_sym_add);

    // 多项式 与 单项式
    register_case(kOptAnd, make_optsign(kOptMul, kOptMul), __land_mul_mul);
    register_case(kOptAnd, make_optsign(kOptAnd, kOptAnd), __land_add_add);
    register_case(kOptAnd, make_optsign(kOptMul, kOptAnd), __land_mul_add);

    // 预处理与后置处理
    register_preprocess(kOptAnd, __land_preprocess);
    register_postprocess(kOptAnd, __land_postprocess);
  }
} // namespace mysym