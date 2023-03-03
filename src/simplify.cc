/* 1. 操作符号“$+$”是一个n元操作符号，链接两个或者两个以上的操作数作为和。
 *    仅有一个操作数，那么操作数只能是**整数**或者**分数**。
 *    例如：$+x$可变为$x$。
 * 2. 操作符号“$*$”是一个n元运算符，链接两个或者两个以上的操作符好作为积。
 *    例如：$2 * 2 *(b*c)$自动化简为$2*a*b*c$。
 * 3. 单目运算“$-$”号与双目运算“$-$”号，**不能**出现在化简后的表达式种。
 *    例如：$-x$需要被化简为$(-1) * x$，负号“$-$”并不是一个单独的操作符号。
 *    例如：$a-2*b$需要被自动化简为$a+(-2)*b$。
 * 4. 双目运算符号“$/$”**不能**出现在化简后的表达式种。简化后端商的表现形式，
 *    需要使用**积**、**指数**与特定的**分数**形式进行表现。
 *    例如：$1/c$表示为$c^{-1}$，$c/d^{2}$被自动化简为$c*d^{-2}$。
 * 5. 数值分数需要满足两个条件：
 *    - 商被表现为一个分数$c/d$，那么$c \neq 0$，$d \neq 0$并且是$c,d$整数，
 *      使用**fraction**操作符进行表示。
 *    - 一个负数的分数，将分子设为负数，分母为正数。
 * 6. 操作符号“^”是双目运算符。如果$u = v^n$，那么$n$是一个整数，
 *    然$v$**不能**是一个**整数**、**分数**、**积**或者**指数**。这个规则蕴含着：
 *    $(a*b)^2$需要简化为：$(a^2)*(b^2)*(c^2)$；$(x^2)^3$要简化成$x^6$；
 *    并且$3^{-1}$要简化成分数$1/3$。
 * 7. 阶乘符号“$!$”是一个单目运算符号，操作数**不能**是一个**非负整数**。
 */
#include <mysym/mysym.h>

namespace mysym
{

  static symbol_t __simplify_function(const symbol_t &s)
  {
    return s;
  }

  static symbol_t __automatic_simplify(const symbol_t &s)
  {
    if (is_sym(kind(s)))
    {
      return s;
    }
    else if (is_frac(kind(s)))
    {
      //
      // 如果是有理数则进行有理数化简
      //
      return simplify_rational_number(s);
    }
    else
    {
      //
      // 进行递归
      //
      symbol_t u = map(__automatic_simplify, s);
      if (is_pow(kind(u)))
        return simplify_pow(u);
      else if (is_mul(kind(u)))
        return simplify_product(u);
      else if (is_add(kind(u)))
        return simplify_sum(u);
      else if (is_fact(kind(u)))
        return simplify_factorial(u);
      else
        return __simplify_function(u);
    }
    return s;
  }

  void automatic_simplify(symbol_t &s, bool reverse)
  {
    //
    // 对多项式排序
    //
    sort(s, reverse);

    //
    // 合并基础运算符并且合并同类项
    //
    merge(s);

    //
    // 对各项进行自动化简
    //
    __automatic_simplify(s);
    return;
  }
} // namespace mysym