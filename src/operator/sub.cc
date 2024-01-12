#include <mysym/mysym.h>
#include <mynum/wrapper.h>
#include "__test.h"

namespace mysym
{
  static bool __handle_sign(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    //
    // 1. 如果x符号为正，y符号为负，则转为减法运算。
    // 2. 如果x符号为负，y符号为正，则转为减法运算y-x。
    // 3. 如果x符号为负，y符号为负，则提出-1并进行-1 * (x+y)。
    // 4. 如果x符号为正，y符号为正，则正常运算。
    //
    int sign_x = sign(x), sign_y = sign(y);
    if ((sign_x == kSignPositive) && (sign_y == kSignNegative))
    {
      z = execute_cases(kOptAdd, x, abs(y));
    }
    else if ((sign_x == kSignNegative) && (sign_y == kSignPositive))
    {
      z = execute_cases(kOptAdd, abs(x), y);
      z = just_make2(kOptMul, gConstNegOne, z);
    }
    else if ((sign_x == kSignNegative) && (sign_y == kSignNegative))
    {
      z = execute_cases(kOptSub, abs(y), abs(x));
    }
    else
    {
      return false;
    }
    return true;
  }

  static bool __handle_infinity(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    //
    // 对♾️的相关计算
    //
    if (is_inf(kind(x)) && is_neg_inf(kind(y)))
      z = gConstInf;
    else if (is_neg_inf(kind(x)) && is_inf(kind(y)))
      z = gConstNegInf;
    else if (is_inf(kind(x)))
      z = gConstInf;
    else if (is_inf(kind(y)))
      z = gConstNegInf;
    else if (is_neg_inf(kind(x)))
      z = gConstNegInf;
    else if (is_neg_inf(kind(y)))
      z = gConstInf;
    else
      return false;
    return true;
  }

  static symbol_t __sub_num_num(const symbol_t &x, const symbol_t &y)
  {
    number_t f1 = number_t(x.literal);
    number_t f2 = number_t(y.literal);
    return number_to_symbol(f1 - f2);
  }

  static symbol_t __sub_num_frac(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = compute_frac_num(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_num_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_num_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_num_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = compute_frac_frac(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_frac_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_frac_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_nature_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_nature_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_var_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_var_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  static symbol_t __sub_log_log(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    symbol_t xb = base(x), yb = base(y);
    symbol_t xe = exponent(x), ye = exponent(y);
    if (compare(xb, yb) == 0)
    {
      z = create(kOptLog);
      append(z, xb);
      symbol_t ze = div(xe, ye);
      append(z, ze);
    }
    else
    {
      if (__handle_sign(x, y, z) == false)
        z = just_make2(kOptSub, x, y);
    }
    return z;
  }

  static symbol_t __sub_func_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptSub, x, y);
    return z;
  }

  //////////////////////////////////////////////////
  // 这里进入单个符号与单项式与多项式的处理
  //////////////////////////////////////////////////

  static symbol_t __sub_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
    {
      symbol_t xt = term(x), xc = constant(x);
      symbol_t yt = term(y), yc = constant(y);
      if (compare(xt, yt) == 0)
      {
        symbol_t c = sub(xc, yc);
        z = just_make2(kOptMul, c, xt);
      }
      else
      {
        z = just_make2(kOptSub, x, y);
      }
    }
    return z;
  }

  static void __order_sym_operand(const symbol_t &x, const symbol_t &y,
                                  symbol_t &_x, symbol_t &_y, opt_t &opt)
  {
    if (is_sym(kind(x)))
    {
      _x = x;
      _y = y;
      opt = kOptSub;
    }
    else
    {
      _x = opposite(y);
      _y = x;
      opt = kOptAdd;
    }
    return;
  }

  static symbol_t __sub_sym_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = create_opt(kOptAdd);
    opt_t opt;
    if (__handle_sign(x, y, z) == false)
    {
      bool s = false;
      symbol_t _x, _y;
      __order_sym_operand(x, y, _x, _y, opt);

      size_t n = size(_y);
      for (size_t i = 0; i < n; i++)
      {
        symbol_t k = execute_cases(opt, _x, _y[i]);

        // 由于_x 与 _y[i]都是单项式或者单个符号，则如果结果
        // 出现+号，则表明_x与_y[i]不能合并。
        if (is_add(kind(k)))
        {
          append(z, _y[i]);
        }
        else
        {
          if (compare(k, gConstZero) != 0)
            append(z, k);
          z.items.insert(z.items.end(), _y.items.begin() + i + 1, _y.items.end());
          s = true;
          break;
        }
      } /* end for */

      if (s == false)
        append(z, _x);
    }
    return z;
  }

  static symbol_t __sub_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
    {
      symbol_t _x = term(x), _y = term(y);
      if (compare(_x, _y) == 0)
      {
        symbol_t xc = constant(x), yc = constant(y);
        symbol_t c = sub(xc, yc);
        z = mul(c, _x);
      }
      else
      {
        z = just_make2(kOptSub, x, y);
      }
    }
    return z;
  }

  static symbol_t __sub_add_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x = x, _y = y, z;
    size_t nx = size(_x), ny = size(_y);
    bool s = false;
    for (size_t i = 0; i < nx; i++)
    {
      //
      // 遍历找到一个可以与_x[i]做减法的_y中的项目
      // 如果找到了，则做运行并将结果保存。
      // 没有找到，则直接保存_x[i]到z中。
      //
      s = false;
      for (size_t j = 0; j < ny; j++)
      {
        symbol_t k = sub(_x[i], _y[j]);
        // 由于_x[i] 与 _y[j]都是单项式或者单个符号，则如果结果
        // 出现+号，则表明_x[i]与_y[j]不能合并。
        if (is_add(kind(k)))
        {
          continue;
        }
        else
        {
          s = true;
          _y.items[j] = k;
          break;
        }
      } /* end for */

      //
      // 记录没有合并的_x[i]
      //
      if (s == false)
      {
        append(z, _x[i]);
      }
    }

    if (size(z) == 0)
      z = just_make2(kOptSub, _x, _y);
    else
      z.items.insert(z.items.end(), _y.items.begin(), _y.items.end());

    return z;
  }

  static symbol_t __sub_mul_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = c_sub(x, y);
    apply_rule(z);
    return z;
  }

  static symbol_t __sub_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    apply_basic_rule(_x);
    return _x;
  }

  static bool __sub_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    //
    // x,y相同的运算
    //
    if (compare(x, y) == 0)
      z = gConstZero;

    //
    // 与0的运算
    //
    else if (compare(x, gConstZero) == 0)
      z = opposite(y);
    else if (compare(y, gConstZero) == 0)
      z = x;

    //
    // 错误情况
    //
    else
      return false;
    return true;
  }

  static symbol_t __sub_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    if (is_basic(kind(_z)))
    {
      // 基础单元运算都是二元运算
      if (size(_z) == 1)
      {
        _z = _z[0];
      }
    }
    sort(_z);
    return _z;
  }

  symbol_t sub(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptSub, x, y);
  }

  void register_sub_rule()
  {
    // 数值 + xxx
    register_case(kOptSub, make_optsign(kOptNumber, kOptNumber), __sub_num_num);
    register_case(kOptSub, make_optsign(kOptNumber, kOptFrac), __sub_num_frac);
    register_case(kOptSub, make_optsign(kOptNumber, "nature"), __sub_num_nature);
    register_case(kOptSub, make_optsign(kOptNumber, kOptVariate), __sub_num_var);
    register_case(kOptSub, make_optsign(kOptNumber, "func"), __sub_num_func);

    // 分数 + xxx
    register_case(kOptSub, make_optsign(kOptFrac, kOptFrac), __sub_frac_frac);
    register_case(kOptSub, make_optsign(kOptFrac, "nature"), __sub_frac_nature);
    register_case(kOptSub, make_optsign(kOptFrac, kOptVariate), __sub_frac_var);
    register_case(kOptSub, make_optsign(kOptFrac, "func"), __sub_frac_func);

    // 常数 + xxx
    register_case(kOptSub, make_optsign("nature", "nature"), __sub_nature_nature);
    register_case(kOptSub, make_optsign("nature", kOptVariate), __sub_nature_var);
    register_case(kOptSub, make_optsign("nature", "func"), __sub_nature_func);

    // 变量 + xxx
    register_case(kOptSub, make_optsign(kOptVariate, kOptVariate), __sub_var_var);
    register_case(kOptSub, make_optsign(kOptVariate, "func"), __sub_var_func);

    // 特别函数
    register_case(kOptSub, make_optsign(kOptPow, kOptPow), __sub_pow_pow);
    register_case(kOptSub, make_optsign(kOptLog, kOptLog), __sub_log_log);

    // 函数 + xxx
    register_case(kOptSub, make_optsign("func", "func"), __sub_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptSub, make_optsign("sym", kOptMul), __sub_sym_mul);
    register_case(kOptSub, make_optsign("sym", kOptAdd), __sub_sym_add);

    // 多项式 与 单项式
    register_case(kOptSub, make_optsign(kOptMul, kOptMul), __sub_mul_mul);
    register_case(kOptSub, make_optsign(kOptAdd, kOptAdd), __sub_add_add);
    register_case(kOptSub, make_optsign(kOptMul, kOptAdd), __sub_mul_add);

    // 入口
    append_entry(kOptSub, __sub_entry, __sub_preprocess, __sub_postprocess);
  }
} // namespace mysym