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
    // 4. 如果x符号为正，y符号为正，则正常运算，直接返回。
    //
    int sign_x = sign(x), sign_y = sign(y);
    if ((sign_x == kSignPositive) && (sign_y == kSignNegative))
    {
      z = execute_cases(kOptSub, x, abs(y));
    }
    else if ((sign_x == kSignNegative) && (sign_y == kSignPositive))
    {
      z = execute_cases(kOptSub, y, abs(x));
    }
    else if ((sign_x == kSignNegative) && (sign_y == kSignNegative))
    {
      z = execute_cases(kOptAdd, abs(x), abs(y));
      z = just_make2(kOptMul, gConstNegOne, z);
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
    if (__test_and_or(is_inf, is_neg_inf, x, y))
      z = gConstZero;
    else if (__test_or(is_inf, x, y))
      z = gConstInf;
    else if (__test_or(is_neg_inf, x, y))
      z = gConstNegInf;
    else
      return false;
    return true;
  }

  static symbol_t __add_num_num(const symbol_t &x, const symbol_t &y)
  {
    number_t f1 = number_t(x.literal);
    number_t f2 = number_t(y.literal);
    return number_to_symbol(f1 + f2);
  }

  static symbol_t __add_num_frac(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = compute_frac_num(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_num_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_num_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_num_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = compute_frac_frac(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_frac_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_frac_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_nature_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_nature_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;

    if (__handle_infinity(x, y, z) == true)
      return z;

    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_var_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_var_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  static symbol_t __add_log_log(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    symbol_t xb = base(x), yb = base(y);
    symbol_t xe = exponent(x), ye = exponent(y);
    if (compare(xb, yb) == 0)
    {
      z = create(kOptLog);
      append(z, xb);
      symbol_t ze = mul(xe, ye);
      append(z, ze);
    }
    else
    {
      if (__handle_sign(x, y, z) == false)
        z = just_make2(kOptAdd, x, y);
    }
    return z;
  }

  static symbol_t __add_func_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
      z = just_make2(kOptAdd, x, y);
    return z;
  }

  //////////////////////////////////////////////////
  // 这里进入单个符号与单项式与多项式的处理
  //////////////////////////////////////////////////
  static void __order_sym_operand(const symbol_t &x, const symbol_t &y,
                                  symbol_t &_x, symbol_t &_y)
  {
    if (is_sym(kind(x)))
    {
      _x = x;
      _y = y;
    }
    else
    {
      _x = y;
      _y = x;
    }
    return;
  }

  static symbol_t __add_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x, _y, z;
    if (__handle_sign(x, y, z) == false)
    {
      __order_sym_operand(x, y, _x, _y);

      symbol_t t = term(_y), c = constant(_y);
      if (compare(_x, t) == 0)
      {
        c = add(c, gConstOne);
        z = just_make2(kOptMul, c, _x);
      }
      else
      {
        z = just_make2(kOptAdd, _x, _y);
      }
    }
    return z;
  }

  static symbol_t __add_sym_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = create_opt(kOptAdd);
    if (__handle_sign(x, y, z) == false)
    {
      bool s = false;
      symbol_t _x, _y;
      __order_sym_operand(x, y, _x, _y);

      size_t n = size(_y);
      for (size_t i = 0; i < n; i++)
      {
        symbol_t k = add(_x, _y[i]);

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

  static symbol_t __add_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_sign(x, y, z) == false)
    {
      symbol_t _x = term(x), _y = term(y);
      if (compare(_x, _y) == 0)
      {
        symbol_t xc = constant(x), yc = constant(y);
        symbol_t c = add(xc, yc);
        z = mul(c, _x);
      }
      else
      {
        z = just_make2(kOptAdd, x, y);
      }
    }
    return z;
  }

  static symbol_t __add_add_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x = x, _y = y, z = create_opt(kOptAdd);;
    size_t nx = size(_x), ny = size(_y);
    bool s = false;
    for (size_t i = 0; i < nx; i++)
    {
      //
      // 遍历找到一个可以与_x[i]做加法的_y中的项目
      // 如果找到了，则做运行并将结果保存。
      // 没有找到，则直接保存_x[i]到z中。
      //
      s = false;
      for (size_t j = 0; j < ny; j++)
      {
        symbol_t k = add(_x[i], _y[j]);
        // 由于_x[i] 与 _y[j]都是单项式或者单个符号，则如果结果
        // 出现+号，则表明_x[i]与_y[j]不能合并。
        if (is_add(kind(k)))
        {
          continue;
        }
        else
        {
          s = true;
          if (compare(k, gConstZero) != 0)
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
      z = just_make2(kOptAdd, _x, _y);
    else
      z.items.insert(z.items.end(), _y.items.begin(), _y.items.end());

    return z;
  }

  static void __order_monomial_operand(const symbol_t &x, const symbol_t &y,
                                       symbol_t &_x, symbol_t &_y)
  {
    if (is_mul(kind(x)))
    {
      _x = x;
      _y = y;
    }
    else
    {
      _x = y;
      _y = x;
    }
    return;
  }

  static symbol_t __add_mul_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x, _y, z = create_opt(kOptAdd);
    __order_monomial_operand(x, y, _x, _y);

    bool s = false;
    size_t n = size(_y);
    for (size_t i = 0; i < n; i++)
    {
      symbol_t k = execute_cases(kOptAdd, _x, _y[i]);

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

    return z;
  }

  static symbol_t __add_entry(const symbol_t &x)
  {
    symbol_t _x = x;
    apply_basic_rule(_x);
    return _x;
  }

  static bool __add_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    //
    // x,y相同的运算
    //
    if (compare(x, y) == 0)
    {
      z = just_make2(kOptMul, "2", x);
    }

    //
    // 与0的运算
    //
    else if (compare(x, gConstZero) == 0)
      z = y;
    else if (compare(y, gConstZero) == 0)
      z = x;

    //
    // 错误情况
    //
    else
      return false;
    return true;
  }

  static symbol_t __add_postprocess(const symbol_t &z)
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

  symbol_t add(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptAdd, x, y);
  }

  void register_add_rule()
  {
    // 数值 + xxx
    register_case(kOptAdd, make_optsign(kOptNumber, kOptNumber), __add_num_num);
    register_case(kOptAdd, make_optsign(kOptNumber, kOptFrac), __add_num_frac);
    register_case(kOptAdd, make_optsign(kOptNumber, "nature"), __add_num_nature);
    register_case(kOptAdd, make_optsign(kOptNumber, kOptVariate), __add_num_var);
    register_case(kOptAdd, make_optsign(kOptNumber, "func"), __add_num_func);

    // 分数 + xxx
    register_case(kOptAdd, make_optsign(kOptFrac, kOptFrac), __add_frac_frac);
    register_case(kOptAdd, make_optsign(kOptFrac, "nature"), __add_frac_nature);
    register_case(kOptAdd, make_optsign(kOptFrac, kOptVariate), __add_frac_var);
    register_case(kOptAdd, make_optsign(kOptFrac, "func"), __add_frac_func);

    // 常数 + xxx
    register_case(kOptAdd, make_optsign("nature", "nature"), __add_nature_nature);
    register_case(kOptAdd, make_optsign("nature", kOptVariate), __add_nature_var);
    register_case(kOptAdd, make_optsign("nature", "func"), __add_nature_func);

    // 变量 + xxx
    register_case(kOptAdd, make_optsign(kOptVariate, kOptVariate), __add_var_var);
    register_case(kOptAdd, make_optsign(kOptVariate, "func"), __add_var_func);

    // 特别函数
    register_case(kOptAdd, make_optsign(kOptPow, kOptPow), __add_pow_pow);
    register_case(kOptAdd, make_optsign(kOptLog, kOptLog), __add_log_log);

    // 函数 + xxx
    register_case(kOptAdd, make_optsign("func", "func"), __add_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptAdd, make_optsign("sym", kOptMul), __add_sym_mul);
    register_case(kOptAdd, make_optsign("sym", kOptAdd), __add_sym_add);

    // 多项式 与 单项式
    register_case(kOptAdd, make_optsign(kOptMul, kOptMul), __add_mul_mul);
    register_case(kOptAdd, make_optsign(kOptAdd, kOptAdd), __add_add_add);
    register_case(kOptAdd, make_optsign(kOptMul, kOptAdd), __add_mul_add);

    // 入口
    append_entry(kOptAdd, __add_entry, __add_preprocess, __add_postprocess);
  }
} // namespace mysym