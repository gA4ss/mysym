#include <mysym/mysym.h>
#include "__misc.h"

namespace mysym
{
  static bool __find_symopt(std::string s)
  {
    return std::find(gSymOpts.begin(), gSymOpts.end(), s) != gSymOpts.end();
  }

  static bool __find_optset(std::string s)
  {
    return std::find(gOptSets.begin(), gOptSets.end(), s) != gOptSets.end();
  }

  bool is_optsign(optsign_t sign)
  {
    std::vector<std::string> s = split_string(sign);
    if (s.size() != 2)
      return false;

    return ((__find_symopt(s[0]) || __find_optset(s[0])) &&
            (__find_symopt(s[1]) || __find_optset(s[1])));
  }

  optsign_t make_optsign(opt_t opt1, opt_t opt2)
  {
    return opt1 + "," + opt2;
  }

  optpair_t split_optcase(optsign_t sign)
  {
    std::vector<std::string> s = split_string(sign);
    mysym_assert(s.size() == 2, "size of optcase is not 2, opc = \'%s\'", sign.c_str());
    return {s[0], s[1]};
  }

  /* p的几种情况
   * 1. i,j都是运算符，且相等
   * 2. i,j都是运算符，但是不相等
   * 3. i,j其中一个是运算符，一个是运算符集合，且运算符在集合内
   * 4. i,j其中一个是运算符，一个是运算符集合，且运算符不在集合内
   * 5. i,j都是运算符集合，且相等
   * 6. i,j都是运算符集合，且一个被一个包含
   * 7. i,j都是运算符集合，且相交
   * 8. i,j都是运算符集合，且无交集
   */
  static int __score_optpair(const optpair_t& p)
  {
    opt_t i = p.first, j = p.second;
    if (is_symopt(i) && is_symopt(j))
    {
      return i == j ? 1 : 2;
    }
    else if (is_symopt(i) && !is_symopt(j))
    {
      return in_optset(j, i) ? 3 : 4;
    }
    else if (!is_symopt(i) && is_symopt(j))
    {
      return in_optset(i, j) ? 3 : 4;
    }
    else
    {
      // 两个都是optset
      set_relation_t rel = relation_optset(i, j);
      if (rel == kSet1Equ2)
        return 5;
      else if ((rel == kSet1Include2) || (rel == kSet2Include1))
        return 6;
      else if (rel == kSetIntersect)
        return 7;
      else if (rel == kSetNoneIntersect)
        return 8;
    }
    return 0;
  }

  // i < j return true else false
  bool cmp_optsign(const optsign_t& i, const optsign_t& j)
  {
    optpair_t ip = split_optcase(i);
    optpair_t jp = split_optcase(j);

    int si = __score_optpair(ip);
    int sj = __score_optpair(jp);

    // FIXME:
    // 这里其实不考虑两个pair的相关性，算法不是很好。有待研究
    return si < sj;
  }

  // i < j return true
  // i >= j return false
  static bool __optcase_cmp(const std::string &i,const std::string &j)
  { 
    // 这里默认了i，j不是symopt就是optset
    // if ((is_symopt(i) || (is_optset(i))) && (is_symopt(j) || (is_optset(j))))
    // {
    //   // 触发异常
    // }

    if (is_symopt(i) && is_symopt(j))
    {
      // 单个运算符号的优先级越高越靠前
      int c = cmp_operator_priority(i, j);
      if (c == 1)
        return true;
      else
        return false;
    }
    else if (is_symopt(i) && !is_symopt(j))
    {
      return true;
    }
    else if (!is_symopt(i) && is_symopt(j))
    {
      return false;
    }
    else 
    {
      // 两个都是optset
      set_relation_t rel = relation_optset(i, j);
      if (rel == kSetNoneIntersect)
        return false;
      else if (rel == kSet1Equ2)
        return false;
      else if (rel == kSet1Include2)
        return false;
      else if (rel == kSet2Include1)
        return true;
      else if (rel == kSetIntersect)
      {
        size_t ni = size_optset(i), nj = size_optset(j);
        if (ni < nj)
          return true;
        else if (ni > nj)
          return false;
        else
        {
          // 集合数量一致判断集合内元素优先级
          // 优先级越高，在队列中越前
          optset_t opts;
          find_optset(i, opts);
          int ip = 0, jp = 0;
          for (auto it = opts.items.elements.begin(); it != opts.items.elements.end(); it++)
            ip += it->second.priority;
          for (auto jt = opts.items.elements.begin(); jt != opts.items.elements.end(); jt++)
            jp += jt->second.priority;
          if (ip > jp)
            return true;
          else
            return false;
        }
      }/* end else if */
    }
    return false;
  }

  // 通过ops产生optcase
  // ops是一个使用','或者空格分割得字符串，字符串得内容是symopt与optset组成。
  // optcase_t是一个字符串队列，将ops中的元素两两匹配。
  //
  optcase_t generate_optcase(std::string ops)
  {
    optcase_t cases;
    std::vector<std::string> sets = split_string(ops);
    std::sort(sets.begin(), sets.end(), __optcase_cmp);
    size_t n = sets.size(), j = 0;
    for (size_t i = 0; i < n; i++)
    {
      j = i;
      for (; j < n; j++)
      {
        cases.push_back(make_optsign(sets[i], sets[j]));
        if (sets[i] != sets[j])
        {
          cases.push_back(make_optsign(sets[j], sets[i]));
        }
      }/* end for */
    }
    return cases;
  }
} // namespace mysym