#include <mysym/mysym.h>

namespace mysym
{
  static symbol_t __equ_num_num(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_num_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_log_log(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_func_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_sym_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_add_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static symbol_t __equ_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptEqu, x, y);
  }

  static bool __equ_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __equ_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  symbol_t equ(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptEqu, x, y);
  }

  void register_equ_rule()
  {
    // 数值 + xxx
    register_case(kOptEqu, make_optsign(kOptNumber, kOptNumber), __equ_num_num);
    register_case(kOptEqu, make_optsign(kOptNumber, kOptFrac), __equ_num_frac);
    register_case(kOptEqu, make_optsign(kOptNumber, "nature"), __equ_num_nature);
    register_case(kOptEqu, make_optsign(kOptNumber, kOptVariate), __equ_num_var);
    register_case(kOptEqu, make_optsign(kOptNumber, "func"), __equ_num_func);

    // 分数 + xxx
    register_case(kOptEqu, make_optsign(kOptFrac, kOptFrac), __equ_frac_frac);
    register_case(kOptEqu, make_optsign(kOptFrac, "nature"), __equ_frac_nature);
    register_case(kOptEqu, make_optsign(kOptFrac, kOptVariate), __equ_frac_var);
    register_case(kOptEqu, make_optsign(kOptFrac, "func"), __equ_frac_func);

    // 常数 + xxx
    register_case(kOptEqu, make_optsign("nature", "nature"), __equ_nature_nature);
    register_case(kOptEqu, make_optsign("nature", kOptVariate), __equ_nature_var);
    register_case(kOptEqu, make_optsign("nature", "func"), __equ_nature_func);

    // 变量 + xxx
    register_case(kOptEqu, make_optsign(kOptVariate, kOptVariate), __equ_var_var);
    register_case(kOptEqu, make_optsign(kOptVariate, "func"), __equ_var_func);

    // 特别函数
    register_case(kOptEqu, make_optsign(kOptPow, kOptPow), __equ_pow_pow);
    register_case(kOptEqu, make_optsign(kOptLog, kOptLog), __equ_log_log);

    // 函数 + xxx
    register_case(kOptEqu, make_optsign("func", "func"), __equ_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptEqu, make_optsign("sym", kOptMul), __equ_sym_mul);
    register_case(kOptEqu, make_optsign("sym", kOptEqu), __equ_sym_add);

    // 多项式 与 单项式
    register_case(kOptEqu, make_optsign(kOptMul, kOptMul), __equ_mul_mul);
    register_case(kOptEqu, make_optsign(kOptEqu, kOptEqu), __equ_add_add);
    register_case(kOptEqu, make_optsign(kOptMul, kOptEqu), __equ_mul_add);

    // 预处理与后置处理
    register_preprocess(kOptEqu, __equ_preprocess);
    register_postprocess(kOptEqu, __equ_postprocess);
  }
} // namespace mysym