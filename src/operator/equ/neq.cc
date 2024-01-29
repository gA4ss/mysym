#include <mysym/mysym.h>

namespace mysym
{
  static symbol_t __neq_num_num(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_num_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_log_log(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_func_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_sym_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_add_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static symbol_t __neq_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNotEqu, x, y);
  }

  static bool __neq_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __neq_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  symbol_t neq(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptNotEqu, x, y);
  }

  void register_neq_rule()
  {
    // 数值 + xxx
    register_case(kOptNotEqu, make_optsign(kOptNumber, kOptNumber), __neq_num_num);
    register_case(kOptNotEqu, make_optsign(kOptNumber, kOptFrac), __neq_num_frac);
    register_case(kOptNotEqu, make_optsign(kOptNumber, "nature"), __neq_num_nature);
    register_case(kOptNotEqu, make_optsign(kOptNumber, kOptVariate), __neq_num_var);
    register_case(kOptNotEqu, make_optsign(kOptNumber, "func"), __neq_num_func);

    // 分数 + xxx
    register_case(kOptNotEqu, make_optsign(kOptFrac, kOptFrac), __neq_frac_frac);
    register_case(kOptNotEqu, make_optsign(kOptFrac, "nature"), __neq_frac_nature);
    register_case(kOptNotEqu, make_optsign(kOptFrac, kOptVariate), __neq_frac_var);
    register_case(kOptNotEqu, make_optsign(kOptFrac, "func"), __neq_frac_func);

    // 常数 + xxx
    register_case(kOptNotEqu, make_optsign("nature", "nature"), __neq_nature_nature);
    register_case(kOptNotEqu, make_optsign("nature", kOptVariate), __neq_nature_var);
    register_case(kOptNotEqu, make_optsign("nature", "func"), __neq_nature_func);

    // 变量 + xxx
    register_case(kOptNotEqu, make_optsign(kOptVariate, kOptVariate), __neq_var_var);
    register_case(kOptNotEqu, make_optsign(kOptVariate, "func"), __neq_var_func);

    // 特别函数
    register_case(kOptNotEqu, make_optsign(kOptPow, kOptPow), __neq_pow_pow);
    register_case(kOptNotEqu, make_optsign(kOptLog, kOptLog), __neq_log_log);

    // 函数 + xxx
    register_case(kOptNotEqu, make_optsign("func", "func"), __neq_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptNotEqu, make_optsign("sym", kOptMul), __neq_sym_mul);
    register_case(kOptNotEqu, make_optsign("sym", kOptNotEqu), __neq_sym_add);

    // 多项式 与 单项式
    register_case(kOptNotEqu, make_optsign(kOptMul, kOptMul), __neq_mul_mul);
    register_case(kOptNotEqu, make_optsign(kOptNotEqu, kOptNotEqu), __neq_add_add);
    register_case(kOptNotEqu, make_optsign(kOptMul, kOptNotEqu), __neq_mul_add);

    // 预处理与后置处理
    register_preprocess(kOptNotEqu, __neq_preprocess);
    register_postprocess(kOptNotEqu, __neq_postprocess);
  }
} // namespace mysym