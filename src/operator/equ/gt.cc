#include <mysym/mysym.h>

namespace mysym
{
  static symbol_t __gt_num_num(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_num_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_log_log(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_func_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_sym_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_add_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static symbol_t __gt_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptGT, x, y);
  }

  static bool __gt_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __gt_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  symbol_t gt(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptGT, x, y);
  }

  void register_gt_rule()
  {
    // 数值 + xxx
    register_case(kOptGT, make_optsign(kOptNumber, kOptNumber), __gt_num_num);
    register_case(kOptGT, make_optsign(kOptNumber, kOptFrac), __gt_num_frac);
    register_case(kOptGT, make_optsign(kOptNumber, "nature"), __gt_num_nature);
    register_case(kOptGT, make_optsign(kOptNumber, kOptVariate), __gt_num_var);
    register_case(kOptGT, make_optsign(kOptNumber, "func"), __gt_num_func);

    // 分数 + xxx
    register_case(kOptGT, make_optsign(kOptFrac, kOptFrac), __gt_frac_frac);
    register_case(kOptGT, make_optsign(kOptFrac, "nature"), __gt_frac_nature);
    register_case(kOptGT, make_optsign(kOptFrac, kOptVariate), __gt_frac_var);
    register_case(kOptGT, make_optsign(kOptFrac, "func"), __gt_frac_func);

    // 常数 + xxx
    register_case(kOptGT, make_optsign("nature", "nature"), __gt_nature_nature);
    register_case(kOptGT, make_optsign("nature", kOptVariate), __gt_nature_var);
    register_case(kOptGT, make_optsign("nature", "func"), __gt_nature_func);

    // 变量 + xxx
    register_case(kOptGT, make_optsign(kOptVariate, kOptVariate), __gt_var_var);
    register_case(kOptGT, make_optsign(kOptVariate, "func"), __gt_var_func);

    // 特别函数
    register_case(kOptGT, make_optsign(kOptPow, kOptPow), __gt_pow_pow);
    register_case(kOptGT, make_optsign(kOptLog, kOptLog), __gt_log_log);

    // 函数 + xxx
    register_case(kOptGT, make_optsign("func", "func"), __gt_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptGT, make_optsign("sym", kOptMul), __gt_sym_mul);
    register_case(kOptGT, make_optsign("sym", kOptGT), __gt_sym_add);

    // 多项式 与 单项式
    register_case(kOptGT, make_optsign(kOptMul, kOptMul), __gt_mul_mul);
    register_case(kOptGT, make_optsign(kOptGT, kOptGT), __gt_add_add);
    register_case(kOptGT, make_optsign(kOptMul, kOptGT), __gt_mul_add);

    // 预处理与后置处理
    register_preprocess(kOptGT, __gt_preprocess);
    register_postprocess(kOptGT, __gt_postprocess);
  }
} // namespace mysym