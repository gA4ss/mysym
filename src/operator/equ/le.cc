#include <mysym/mysym.h>


namespace mysym
{
  static symbol_t __le_num_num(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_num_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_log_log(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_func_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_sym_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_add_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static symbol_t __le_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptLE, x, y);
  }

  static bool __le_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __le_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  symbol_t le(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptLE, x, y);
  }

  void register_le_rule()
  {
    // 数值 + xxx
    register_case(kOptLE, make_optsign(kOptNumber, kOptNumber), __le_num_num);
    register_case(kOptLE, make_optsign(kOptNumber, kOptFrac), __le_num_frac);
    register_case(kOptLE, make_optsign(kOptNumber, "nature"), __le_num_nature);
    register_case(kOptLE, make_optsign(kOptNumber, kOptVariate), __le_num_var);
    register_case(kOptLE, make_optsign(kOptNumber, "func"), __le_num_func);

    // 分数 + xxx
    register_case(kOptLE, make_optsign(kOptFrac, kOptFrac), __le_frac_frac);
    register_case(kOptLE, make_optsign(kOptFrac, "nature"), __le_frac_nature);
    register_case(kOptLE, make_optsign(kOptFrac, kOptVariate), __le_frac_var);
    register_case(kOptLE, make_optsign(kOptFrac, "func"), __le_frac_func);

    // 常数 + xxx
    register_case(kOptLE, make_optsign("nature", "nature"), __le_nature_nature);
    register_case(kOptLE, make_optsign("nature", kOptVariate), __le_nature_var);
    register_case(kOptLE, make_optsign("nature", "func"), __le_nature_func);

    // 变量 + xxx
    register_case(kOptLE, make_optsign(kOptVariate, kOptVariate), __le_var_var);
    register_case(kOptLE, make_optsign(kOptVariate, "func"), __le_var_func);

    // 特别函数
    register_case(kOptLE, make_optsign(kOptPow, kOptPow), __le_pow_pow);
    register_case(kOptLE, make_optsign(kOptLog, kOptLog), __le_log_log);

    // 函数 + xxx
    register_case(kOptLE, make_optsign("func", "func"), __le_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptLE, make_optsign("sym", kOptMul), __le_sym_mul);
    register_case(kOptLE, make_optsign("sym", kOptLE), __le_sym_add);

    // 多项式 与 单项式
    register_case(kOptLE, make_optsign(kOptMul, kOptMul), __le_mul_mul);
    register_case(kOptLE, make_optsign(kOptLE, kOptLE), __le_add_add);
    register_case(kOptLE, make_optsign(kOptMul, kOptLE), __le_mul_add);

    // 预处理与后置处理
    register_preprocess(kOptLE, __le_preprocess);
    register_postprocess(kOptLE, __le_postprocess);
  }
} // namespace mysym