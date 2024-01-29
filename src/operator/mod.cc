#include <mysym/mysym.h>
#include <mynum/wrapper.h>
#include "__test.h"

namespace mysym
{
  static symbol_t __mod_num_num(const symbol_t &x, const symbol_t &y)
  {
    number_t f1 = mynum::integer_to_float(number_t(x.literal));
    number_t f2 = mynum::integer_to_float(number_t(y.literal));
    return number_to_symbol(f1 % f2);
  }

  static symbol_t __mod_num_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_num_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_num_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_num_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_frac_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_frac_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_nature_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_nature_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_var_var(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_var_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_log_log(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_func_func(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_sym_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_add_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static symbol_t __mod_mul_add(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptMod, x, y);
  }

  static bool __mod_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __mod_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    sort(_z);
    return _z;
  }

  symbol_t mod(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptMod, x, y);
  }

  void register_mod_rule()
  {
    // 数值 + xxx
    register_case(kOptMod, make_optsign(kOptNumber, kOptNumber), __mod_num_num);
    register_case(kOptMod, make_optsign(kOptNumber, kOptFrac), __mod_num_frac);
    register_case(kOptMod, make_optsign(kOptNumber, "nature"), __mod_num_nature);
    register_case(kOptMod, make_optsign(kOptNumber, kOptVariate), __mod_num_var);
    register_case(kOptMod, make_optsign(kOptNumber, "func"), __mod_num_func);

    // 分数 + xxx
    register_case(kOptMod, make_optsign(kOptFrac, kOptFrac), __mod_frac_frac);
    register_case(kOptMod, make_optsign(kOptFrac, "nature"), __mod_frac_nature);
    register_case(kOptMod, make_optsign(kOptFrac, kOptVariate), __mod_frac_var);
    register_case(kOptMod, make_optsign(kOptFrac, "func"), __mod_frac_func);

    // 常数 + xxx
    register_case(kOptMod, make_optsign("nature", "nature"), __mod_nature_nature);
    register_case(kOptMod, make_optsign("nature", kOptVariate), __mod_nature_var);
    register_case(kOptMod, make_optsign("nature", "func"), __mod_nature_func);

    // 变量 + xxx
    register_case(kOptMod, make_optsign(kOptVariate, kOptVariate), __mod_var_var);
    register_case(kOptMod, make_optsign(kOptVariate, "func"), __mod_var_func);

    // 特别函数
    register_case(kOptMod, make_optsign(kOptPow, kOptPow), __mod_pow_pow);
    register_case(kOptMod, make_optsign(kOptLog, kOptLog), __mod_log_log);

    // 函数 + xxx
    register_case(kOptMod, make_optsign("func", "func"), __mod_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptMod, make_optsign("sym", kOptMul), __mod_sym_mul);
    register_case(kOptMod, make_optsign("sym", kOptMod), __mod_sym_add);

    // 多项式 与 单项式
    register_case(kOptMod, make_optsign(kOptMul, kOptMul), __mod_mul_mul);
    register_case(kOptMod, make_optsign(kOptMod, kOptMod), __mod_add_add);
    register_case(kOptMod, make_optsign(kOptMul, kOptMod), __mod_mul_add);

    // 预处理与后置处理
    register_preprocess(kOptMod, __mod_preprocess);
    register_postprocess(kOptMod, __mod_postprocess);
  }
} // namespace mysym