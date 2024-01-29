#include <mysym/mysym.h>
#include <mynum/wrapper.h>
#include "__test.h"

namespace mysym
{
  //
  // 本函数仅在xxx_func中使用
  //
  static bool __handle_pow(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    if (is_pow(kind(x)) && (!is_pow(kind(y))))
    {
      symbol_t xe = exponent(x);
      symbol_t xb = base(x);
      int xs = sign(xe);

      if (xs == kSignNegative)
      {
        z = div(y, pow(xb, abs(xe)));
      }
      else if (compare(xb, y) == 0)
      {
        xe = add(xe, gConstOne);
        z = pow(xb, xe);
      }
      else
      {
        return false;
      }
    }
    else if (is_pow(kind(y)) && !is_pow(kind(x)))
    {
      symbol_t ye = exponent(y);
      symbol_t yb = base(y);
      // int ys = sign(ye);

      //
      // 这里没有判断正负
      //
      if (compare(x, yb) == 0)
      {
        ye = add(ye, gConstOne);
        z = pow(yb, ye);
      }
      else
      {
        return false;
      }
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
      z = gConstNegInf;
    else if ((is_inf(kind(x))) && (sign(y) == kSignPositive))
      z = gConstInf;
    else if ((is_inf(kind(y))) && (sign(x) == kSignPositive))
      z = gConstInf;
    else if ((is_neg_inf(kind(x))) && (sign(y) == kSignPositive))
      z = gConstNegInf;
    else if ((is_neg_inf(kind(y))) && (sign(x) == kSignPositive))
      z = gConstNegInf;
    else if ((is_inf(kind(x))) && (sign(y) == kSignNegative))
      z = gConstNegInf;
    else if ((is_inf(kind(y))) && (sign(x) == kSignNegative))
      z = gConstNegInf;
    else if ((is_neg_inf(kind(x))) && (sign(y) == kSignNegative))
      z = gConstInf;
    else if ((is_neg_inf(kind(y))) && (sign(x) == kSignNegative))
      z = gConstInf;
    else
      return false;
    return true;
  }

  static bool __handle_one(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    if (compare(x, gConstOne) == 0)
      z = y;
    else if (compare(y, gConstOne) == 0)
      z = x;
    else
      return false;
    return true;
  }

  static symbol_t __handle_default(const symbol_t &x, const symbol_t &y)
  {
    if (compare(x, y) == 0)
      return just_make2(kOptPow, x, create_int("2"));
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_num_num(const symbol_t &x, const symbol_t &y)
  {
    number_t f1 = number_t(x.literal);
    number_t f2 = number_t(y.literal);
    return number_to_symbol(f1 * f2);
  }

  static symbol_t __mul_num_frac(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_one(x, y, z) == true)
      return z;
    z = compute_frac_num(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_num_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    else if (__handle_one(x, y, z) == true)
      return z;
    z = just_make2(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_num_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_one(x, y, z) == true)
      return z;
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_num_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_one(x, y, z) == true)
      return z;
    else if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_frac_frac(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_one(x, y, z) == true)
      return z;
    return compute_frac_frac(kOptMul, x, y);
  }

  static symbol_t __mul_frac_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    else if (__handle_one(x, y, z) == true)
      return z;
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_frac_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_one(x, y, z) == true)
      return z;
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_frac_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_one(x, y, z) == true)
      return z;
    else if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_nature_nature(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    return __handle_default(x, y);
  }

  static symbol_t __mul_nature_var(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    return just_make2(kOptMul, x, y);
  }

  static symbol_t __mul_nature_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_infinity(x, y, z) == true)
      return z;
    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_var_var(const symbol_t &x, const symbol_t &y)
  {
    return __handle_default(x, y);
  }

  static symbol_t __mul_var_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_pow(x, y, z) == false)
      z = just_make2(kOptMul, x, y);
    return z;
  }

  static symbol_t __mul_pow_pow(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    symbol_t xb = base(x), yb = base(y);
    symbol_t xe = exponent(x), ye = exponent(y);

    if (compare(xb, yb) == 0)     // 底数相同
    {
      z = create(kOptPow);
      append(z, xb);
      symbol_t ze = add(xe, ye);
      append(z, ze);
    }
    else
    {
      int xs = sign(exponent(x)), ys = sign(exponent(y));
      if ((xs == kSignNegative) && (ys == kSignNegative))
      {
        z = div(gConstOne, mul(pow(xb, abs(xe)), pow(yb, abs(ye))));
      }
      else if ((xs == kSignNegative) && (ys == kSignPositive))
      {
        z = div(y, pow(xb, abs(xe)));
      }
      else if ((xs == kSignPositive) && (ys == kSignNegative))
      {
        z = div(x, pow(yb, abs(ye)));
      }
      else // ((xs == kSignPositive) && (y_sign == kSignPositive))
      {
        z = just_make2(kOptMul, x, y);
      }
    }
    return z;
  }

  static symbol_t __mul_log_log(const symbol_t &x, const symbol_t &y)
  {
    return __handle_default(x, y);
  }

  static symbol_t __mul_func_func(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z;
    if (__handle_pow(x, y, z) == false)
      z = __handle_default(x, y);
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

  static symbol_t __mul_sym_mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x, _y, z = create_opt(kOptMul);
    if (__handle_pow(x, y, z) == false)
    {
      __order_sym_operand(x, y, _x, _y);
      bool s = false;
      size_t ny = size(_y);
      for (size_t i = 0; i < ny; i++)
      {
        symbol_t k = mul(_x, _y[i]);
        if (is_mul(kind(k)))
        {
          append(z, _y[i]);
        }
        else
        {
          if (compare(k, gConstOne) != 0)
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

  static symbol_t __mul_sym_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x, _y, z = create_opt(kOptAdd);
    if (__handle_pow(x, y, z) == false)
    {
      __order_sym_operand(x, y, _x, _y);
      size_t ny = size(_y);
      for (size_t i = 0; i < ny; i++)
      {
        symbol_t k = mul(_x, _y[i]);
        append(z, k);
      } /* end for */
    }
    return iterate(add, z.items);
  }

  static symbol_t __mul_mul_mul(const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x = x, _y = y, z = create_opt(kOptMul);
    size_t nx = size(_x), ny = size(_y);
    std::vector<size_t> used_x;
    for (size_t i = 0; i < nx; i++)
    {
      //
      // 遍历找到一个可以与_x[i]做乘法的_y中的项目
      // 如果找到了，则做运行并将结果保存。
      // 没有找到，则直接保存_x[i]到z中。
      //
      for (size_t j = 0; j < ny; j++)
      {
        symbol_t k = mul(_x[i], _y[j]);
        // 由于_x[i] 与 _y[j]都是单项式或者单个符号，则如果结果
        // 出现*号，则表明_x[i]与_y[j]不能合并。
        if (is_mul(kind(k)))
        {
          continue;
        }
        else
        {
          if (compare(k, gConstOne) != 0)
            _y.items[j] = k;
          used_x.push_back(i);
          break;
        }
      } /* end for */
    }

    //
    // 将没有用的_x的值都合并到结果中。
    //
    z = _y;
    for (size_t i = 0; i < nx; i++)
    {
      if (std::find(used_x.begin(), used_x.end(), i) != used_x.end())
        continue;
      append(z, _x[i]);
    }
    return z;
  }

  static symbol_t __mul_add_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t z = create_opt(kOptAdd);

    size_t nx = size(x), ny = size(y);
    std::vector<size_t> used_x;
    for (size_t i = 0; i < nx; i++)
    {
      for (size_t j = 0; j < ny; j++)
      {
        symbol_t k = mul(x[i], y[j]);
        append(z, k);
      } /* end for */
    }
    return iterate(add, z.items);
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

  static symbol_t __mul_mul_add(const symbol_t &x, const symbol_t &y)
  {
    symbol_t _x, _y, z = create_opt(kOptAdd);
    __order_monomial_operand(x, y, _x, _y);
    size_t ny = size(_y);
    for (size_t i = 0; i < ny; i++)
    {
      symbol_t k = mul(_x, _y[i]);
      append(z, k);
    } /* end for */
    return iterate(add, z.items);
  }

  static bool __mul_preprocess(const symbol_t &x, const symbol_t &y, symbol_t &z)
  {
    return false;
  }

  static symbol_t __mul_postprocess(const symbol_t &z)
  {
    symbol_t _z = z;
    if (is_normal(kind(_z)))
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

  symbol_t mul(const symbol_t &x, const symbol_t &y)
  {
    return execute_cases(kOptMul, x, y);
  }

  void register_mul_rule()
  {
    // 数值 + xxx
    register_case(kOptMul, make_optsign(kOptNumber, kOptNumber), __mul_num_num);
    register_case(kOptMul, make_optsign(kOptNumber, kOptFrac), __mul_num_frac);
    register_case(kOptMul, make_optsign(kOptNumber, "nature"), __mul_num_nature);
    register_case(kOptMul, make_optsign(kOptNumber, kOptVariate), __mul_num_var);
    register_case(kOptMul, make_optsign(kOptNumber, "func"), __mul_num_func);

    // 分数 + xxx
    register_case(kOptMul, make_optsign(kOptFrac, kOptFrac), __mul_frac_frac);
    register_case(kOptMul, make_optsign(kOptFrac, "nature"), __mul_frac_nature);
    register_case(kOptMul, make_optsign(kOptFrac, kOptVariate), __mul_frac_var);
    register_case(kOptMul, make_optsign(kOptFrac, "func"), __mul_frac_func);

    // 常数 + xxx
    register_case(kOptMul, make_optsign("nature", "nature"), __mul_nature_nature);
    register_case(kOptMul, make_optsign("nature", kOptVariate), __mul_nature_var);
    register_case(kOptMul, make_optsign("nature", "func"), __mul_nature_func);

    // 变量 + xxx
    register_case(kOptMul, make_optsign(kOptVariate, kOptVariate), __mul_var_var);
    register_case(kOptMul, make_optsign(kOptVariate, "func"), __mul_var_func);

    // 特别函数
    register_case(kOptMul, make_optsign(kOptPow, kOptPow), __mul_pow_pow);
    register_case(kOptMul, make_optsign(kOptLog, kOptLog), __mul_log_log);

    // 函数 + xxx
    register_case(kOptMul, make_optsign("func", "func"), __mul_func_func);

    // 符号(数值、分数、常数、变量、函数) + 单项式 or 多项式
    register_case(kOptMul, make_optsign("sym", kOptMul), __mul_sym_mul);
    register_case(kOptMul, make_optsign("sym", kOptAdd), __mul_sym_add);

    // 多项式 与 单项式
    register_case(kOptMul, make_optsign(kOptMul, kOptMul), __mul_mul_mul);
    register_case(kOptMul, make_optsign(kOptAdd, kOptAdd), __mul_add_add);
    register_case(kOptMul, make_optsign(kOptMul, kOptAdd), __mul_mul_add);

    // 预处理与后置处理
    register_preprocess(kOptMul, __mul_preprocess);
    register_postprocess(kOptMul, __mul_postprocess);
  }
} // namespace mysym