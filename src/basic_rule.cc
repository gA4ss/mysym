#include <mysym/mysym.h>
#include <unordered_set>

namespace mysym
{
  void apply_associative_law(symbol_t &x)
  {
    merge(x);
  }

  /* 交换律就是排序
   */
  void apply_commutative_law(symbol_t &x)
  {
    sort(x);
  }

  /* 在现实意义中的数学仅有*法对+法的分配律
   * a*(x+y) = ax + ay的形式，这里定义的
   * 分配律更为宽泛，这里的定义可以容纳更多
   * 的运算符，更加抽象。
   *
   * 这里的分配律，如果遇到两个可以运算的符号
   * 但是不进行合并运算。
   *
   * 这里的实现其实也包含了结合律的实现，如果
   * 主符号遇到子项中的符号是相同的，则自动进行
   * 结合律操作，直接合并。
   */
  static symbol_t __apply_distributive_law(opt_t opt, const symbol_t &x, const symbol_t &y)
  {
    if (!can_distributive(opt, kind(y)))
    {
      // 不能分配则将x与y合并成一项，这里使用just_make不进行任何自动的排序。
      return just_make2(opt, x, y);
    }

    //
    // 首先将x作为单独的一个项目，无视x是一个单项还是多项
    //
    opt_t yopt = kind(y);
    symbol_t z = map(y, x, opt);
    //
    // 这里如果x = (a+b)   y = (d+c) 这种形式
    // 那么xy = (a+b)d + (a+b)c
    // 所以这里遍历新生成的z的子项目，随后输出
    //
    for (auto it = z.items.begin(); it != z.items.end(); it++)
    {
      apply_distributive_law(*it);
    }
    return z;
  }
  void apply_distributive_law(symbol_t &x)
  {
    if (!opt_distributive_law(kind(x)))
      return;

    opt_t opt = kind(x);
    size_t n = symbol_size(x);
    if (n == 0)
    {
      // 无运算直接退出，这是一个错误
      // FIXME : 应该抛出异常
      return;
    }
    else if (n == 1)
    {
      // 如果仅一个，则是为在主运算符下与自身的单位做
      // 运算，直接将子项的符号替换到外部即可。然后
      // 继续递归。
      x = *(x.items.begin());
      apply_distributive_law(x);
      return;
    }

    //
    // 这里的n肯定大于等于2
    //
    mysym_assert(n >= 2, "%s", "symbol size = \'%lu\' less than 2", n);

    //
    // 遍历随后节点
    //
    symbol_t _x = operand(x, 0);
    apply_distributive_law(_x); // 对自身子节点应用分配律，进行展开。
    size_t i = 1;
    do
    {
      symbol_t _y = operand(x, i);
      apply_distributive_law(_y); // 对自身子节点应用分配律，进行展开。
      _x = __apply_distributive_law(opt, _x, _y);
      ++i;
    } while (i < n);

    // 更新x
    x = _x;
    return;
  }

  static void __combine_like_terms(symbol_t &x)
  {
    // 不满足结合律的运算不进行结合
    if (!opt_associative_law(kind(x)))
      return;

    symbol_t z, t;
    list_t new_symbol_items;
    std::unordered_set<size_t> combined;
    bool new_z = false;

    opt_t opt = kind(x);
    size_t j = 0, n = symbol_size(x);
    for (size_t i = 0; i < n - 1; i++)
    {
      // 已经在处理节点中的则跳过
      if (std::find(combined.begin(), combined.end(), i) != combined.end())
      {
        continue;
      }

      //
      // 取得本轮计算的第一个符号
      //
      z = operand(x, i);
      new_z = false; // 重置符号

      //
      // 这里更新j的索引，之前的j能合并都进行了合并，它的索引应当在i之后。
      //
      j = i + 1;

      //
      // 每次都是从j
      //
      for (; j < n; j++)
      {
        // 已经在处理节点中的则跳过
        if (std::find(combined.begin(), combined.end(), j) != combined.end())
          continue;

        t = execute_cases(opt, z, operand(x, j));

        //
        // 如果z的运算符与opt一致，则说明两项没有合并，不一致则说明合并了
        // 合并后，记录当前j节点。之后遇到则跳过。
        //
        if (kind(t) != opt)
        {
          combined.insert(j);
          z = t;
          new_z = true;
        }
      }/* j的循环 */

      //
      // 判断改变标志，改变了则压入新的队列
      //
      if (new_z)
      {
        // 有新的z产生说明当前i也被合并了
        combined.insert(i);
        new_symbol_items.push_back(z);
      }
    } /* i的循环 */

    //
    // 如果新的符号队列为空，则说明x的各个项都不能合并
    // 如果新的符号队列不为空，则替换。
    //
    if (new_symbol_items.size() != 0)
    {
      symbol_t _x; _x.opt = kind(x);

      //
      // 全部都结合了并且结果为1，说明所有符号都经过了合并。直接替换
      //
      if ((combined.size() == symbol_size(x)) && (new_symbol_items.size() == 1))
      {
        _x = new_symbol_items[0];
      }
      else
      {
        _x.items = new_symbol_items;
        //
        // 将未参与合并的符号压入结果
        //
        for (size_t k = 0; k < symbol_size(x); k++)
        {
          // 不在已经合并索引中
          if (combined.find(k) == combined.end())
            append(_x, operand(x, k));
        }
      }

      // 更新结果
      x = _x;
    }
    return;
  }

  void combine_like_terms(symbol_t &x)
  {
    // 不满足结合律的运算不进行结合
    if (!opt_associative_law(kind(x)))
      return;

    opt_t opt = kind(x);
    size_t n = symbol_size(x);

    //
    // 这里的合并原则是多次合并(a+b)(c+d) = ac + ad + bc + bd
    // 如果ac与ad在合并后可以继续合并，则继续迭代此流程，直到 + 号
    // 被合并完毕。或者每项都不能再次合并后跳出循环。
    //
    do
    {
      __combine_like_terms(x);

      // 合并后的长度与原先一致则跳出，说明每项都是不同类型的子项目
      // 没有经过任何合并
      if (symbol_size(x) == n)
      {
        break;
      }

      mysym_assert(symbol_size(x) < n, "new symbols size = \'%lu\' greater than \'%lu\'",
                   symbol_size(x), n);
      n = symbol_size(x);
    } while (kind(x) != opt);
    return;
  }

  void format(symbol_t &x)
  {
    apply_associative_law(x);
    apply_distributive_law(x);
    apply_commutative_law(x);
  }

  void apply_basic_rule(symbol_t &x)
  {
    apply_associative_law(x);
    apply_distributive_law(x);
    apply_commutative_law(x);
    combine_like_terms(x);
  }

} // namespace mysym