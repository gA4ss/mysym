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

  optsign_t make_optsign_any(opt_t opt)
  {
    return opt + "," + "all";
  }

  optsign_t make_optsign_exclude(opt_t opt)
  {
    optset_t optset = create_optset_exclude(random_string(), opt);
    return opt + "," + optset.name;
  }

  optpair_t split_optsign(optsign_t sign)
  {
    std::vector<std::string> s = split_string(sign);
    mysym_assert(s.size() == 2, "size of optcase is not 2, opc = \'%s\'", sign.c_str());
    return {s[0], s[1]};
  }

  /* 如果一个运算符集合内的运算符的优先级都是一致的
   * 则将这个集合当作一个符号
   */
  // static bool __is_symopt(const opt_t &opt)
  // {
  //   if (is_symopt(opt))
  //     return true;
  //   return as_symopt(opt);
  // }

  static double __priority(const opt_t &opt)
  {
    if (is_symopt(opt))
      return opt_priority(opt);
    return optset_priority(opt);
  }

  static int __cmp_priority(const opt_t &opt1, const opt_t &opt2)
  {
    double p1 = is_symopt(opt1) ? opt_priority(opt1) : optset_priority(opt1);
    double p2 = is_symopt(opt2) ? opt_priority(opt2) : optset_priority(opt2);
    return p1 == p2 ? 0 : p1 < p2 ? -1 : 1;
  }

  static std::pair<opt_t, opt_t> __on_symopt_optset_order(const opt_t &opt1, const opt_t &opt2)
  {
    opt_t s, os;
    if (is_symopt(opt1))
    {
      s = opt1;
      os = opt2;
    }
    else
    {
      s = opt2;
      os = opt1;
    }
    return {s, os};
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
  static std::pair<int, double> __score_optpair(const optpair_t& p)
  {
    int mode = 0;
    double score = 0.0, p1 = 0.0, p2 = 0.0;
    opt_t i = p.first, j = p.second;
    if (is_symopt(i) && is_symopt(j))
    {
      mode = i == j ? 1 : 2;
      p1 = __priority(i); p2 = __priority(j);
      score = p1 > p2 ? p1 : p2;
    }
    else if (is_symopt(i) && !is_symopt(j))
    {
      if (in_optset(j, i))
      {
        mode = 3;
        // score = optset_priority(j);
        score = opt_priority(i);
      }
      else
      {
        mode = 4;
        // p1 = __priority(i); p2 = __priority(j);
        // score = p1 > p2 ? p1 : p2;
        score = opt_priority(i);
      }
    }
    else if (!is_symopt(i) && is_symopt(j))
    {
      if (in_optset(i, j))
      {
        mode = 3;
        // score = optset_priority(i);
        score = opt_priority(j);
      }
      else
      {
        mode = 4;
        // p1 = __priority(i); p2 = __priority(j);
        // score = p1 > p2 ? p1 : p2;
        score = opt_priority(j);
      }
    }
    else
    {
      // 两个都是optset
      set_relation_t rel = relation_optset(i, j);
      if (rel == kSet1Equ2)
      {
        mode = 5;
        score = optset_priority(i);
      }
      else if (rel == kSet1Include2)
      {
        mode = 6;
        score = optset_priority(i);
      }
      else if (rel == kSet2Include1)
      {
        mode = 6;
        score = optset_priority(j);
      }
      else if ((rel == kSetIntersect) || (rel == kSetNoneIntersect))
      {
        mode = rel == kSetIntersect ? 7 : 8;
        p1 = __priority(i); p2 = __priority(j);
        score = p1 > p2 ? p1 : p2;
      }
    }
    return {mode, score};
  }

// #define __DETAIL_CMP_MODE_NOT_MATCHED         1
#ifdef __DETAIL_CMP_MODE_NOT_MATCHED
  // 注意!!!
  // 以下的__cmp_when_x中i与j不可能拥有相同的模式
  // 它们在模式判断不同下被调用。
  //
#define __switch_opt_pair_score(mode, ip, jp, si, sj, xp, yp, sx, sy, xmd) \
{                       \
  if (si.first == mode) \
  {                     \
    xp = ip; yp = jp;   \
    sx = si; sy = sj;   \
    xmd = true;         \
  } else {              \
    xp = jp; yp = ip;   \
    sx = sj; sy = si;   \
    xmd = false;        \
  }                     \
}

  static bool __cmp_when_1(const optpair_t& ip, const optpair_t& jp, const std::pair<int, double> &si, const std::pair<int, double> &sj)
  {
    bool r = true, xmd = false;
    optpair_t xp, yp;
    std::pair<int, double> sx, sy;
    __switch_opt_pair_score(1, ip, jp, si, sj, xp, yp, sx, sy, xmd);
    int ym = sy.first;
    if (ym == 2)
    {
      r = sx.second > sy.second ? true : false;
    }
    else if (ym == 3)
    {
      //
      // 取出yp的符号部分，以符号优先级为优先
      // 返回的优先级是集合的优先级
      //
      // std::pair<opt_t, opt_t> pp = __on_symopt_optset_order(yp.first, yp.second);
      // r = sx.second > opt_priority(pp.first) ? true : false;
      r = sx.second > sy.second ? true : false;
    }
    else if (ym == 4)
    {
      // 以符号优先级为标准
      // std::pair<opt_t, opt_t> pp = __on_symopt_optset_order(yp.first, yp.second);
      // r = sx.second > opt_priority(pp.first) ? true : false;
      r = sx.second > sy.second ? true : false;
    }
    else if ((ym == 5) || (ym == 6) || (ym == 7) || (ym == 8))
    {
      r = sx.second > sy.second ? true : false;
    }
    return r & xmd;
  }

  static bool __cmp_when_2(const optpair_t& ip, const optpair_t& jp, const std::pair<int, double> &si, const std::pair<int, double> &sj)
  {
    bool r = true, xmd = false;
    optpair_t xp, yp;
    std::pair<int, double> sx, sy;
    __switch_opt_pair_score(2, ip, jp, si, sj, xp, yp, sx, sy, xmd);
    int ym = sy.first;
    if (ym == 3)
    {
      //
      // 取出yp的符号部分，以符号优先级为优先
      // 返回的优先级是集合的优先级
      //
      // std::pair<opt_t, opt_t> pp = __on_symopt_optset_order(yp.first, yp.second);
      // r = sx.second > opt_priority(pp.first) ? true : false;
      r = sx.second > sy.second ? true : false;
    }
    else if (ym == 4)
    {
      // 以符号优先级为标准
      // std::pair<opt_t, opt_t> pp = __on_symopt_optset_order(yp.first, yp.second);
      // r = sx.second > opt_priority(pp.first) ? true : false;
      r = sx.second > sy.second ? true : false;
    }
    else if ((ym == 5) || (ym == 6) || (ym == 7) || (ym == 8))
    {
      r = sx.second > sy.second ? true : false;
    }
    return r & xmd;
  }

  static bool __cmp_when_3(const optpair_t& ip, const optpair_t& jp, const std::pair<int, double> &si, const std::pair<int, double> &sj)
  {
    bool r = true, xmd = false;
    optpair_t xp, yp;
    std::pair<int, double> sx, sy;
    __switch_opt_pair_score(3, ip, jp, si, sj, xp, yp, sx, sy, xmd);
    int ym = sy.first;
    if (ym == 4)
    {
      // 取出两个对的符号部分做比较
      // std::pair<opt_t, opt_t> pp1 = __on_symopt_optset_order(xp.first, xp.second);
      // std::pair<opt_t, opt_t> pp2 = __on_symopt_optset_order(yp.first, yp.second);
      // r = opt_priority(pp1.first) > opt_priority(pp2.first) ? true : false;
      r = sx.second > sy.second ? true : false;
    }
    else if ((ym == 5) || (ym == 6) || (ym == 7) || (ym == 8))
    {
      r = sx.second > sy.second ? true : false;
    }
    return r & xmd;
  }

  static bool __cmp_when_4(const optpair_t& ip, const optpair_t& jp, const std::pair<int, double> &si, const std::pair<int, double> &sj)
  {
    bool r = true, xmd = false;
    optpair_t xp, yp;
    std::pair<int, double> sx, sy;
    __switch_opt_pair_score(4, ip, jp, si, sj, xp, yp, sx, sy, xmd);
    int ym = sy.first;
    if ((ym == 5) || (ym == 6) || (ym == 7) || (ym == 8))
    {
      r = sx.second > sy.second ? true : false;
    }
    return r & xmd;
  }

  static bool __cmp_when_5(const optpair_t& ip, const optpair_t& jp, const std::pair<int, double> &si, const std::pair<int, double> &sj)
  {
    bool r = true, xmd = false;
    optpair_t xp, yp;
    std::pair<int, double> sx, sy;
    __switch_opt_pair_score(5, ip, jp, si, sj, xp, yp, sx, sy, xmd);
    int ym = sy.first;
    if ((ym == 6) || (ym == 7) || (ym == 8))
    {
      r = sx.second > sy.second ? true : false;
    }
    return r & xmd;
  }

  static bool __cmp_when_6(const optpair_t& ip, const optpair_t& jp, const std::pair<int, double> &si, const std::pair<int, double> &sj)
  {
    bool r = true, xmd = false;
    optpair_t xp, yp;
    std::pair<int, double> sx, sy;
    __switch_opt_pair_score(6, ip, jp, si, sj, xp, yp, sx, sy, xmd);
    int ym = sy.first;
    if ((ym == 7) || (ym == 8))
    {
      r = sx.second > sy.second ? true : false;
    }
    return r & xmd;
  }

  static bool __cmp_when_7(const optpair_t& ip, const optpair_t& jp, const std::pair<int, double> &si, const std::pair<int, double> &sj)
  {
    bool r = true, xmd = false;
    optpair_t xp, yp;
    std::pair<int, double> sx, sy;
    __switch_opt_pair_score(7, ip, jp, si, sj, xp, yp, sx, sy, xmd);
    int ym = sy.first;
    if (ym == 8)
    {
      r = sx.second > sy.second ? true : false;
    }
    return r & xmd;
  }
#endif

  // i < j return true else false
  bool cmp_optsign(const optsign_t& i, const optsign_t& j)
  {
    optpair_t ip = split_optsign(i);
    optpair_t jp = split_optsign(j);

    std::pair<int, double> si = __score_optpair(ip), sj = __score_optpair(jp);
    bool r = false;

    //  如果两个分值一致，则考虑考虑细则
    if (si.first == sj.first)
    {
      switch (si.first)
      {
      case 1: // i,j都是运算符，且相等
      {
        r = si.second > sj.second ? true : false; // 优先级越大，越靠前
      } break;
      case 2: // i,j都是运算符，但是不相等
      {
        r = si.second > sj.second ? true : false; // 优先级越大，越靠前
      } break;
      case 3: // i,j其中一个是运算符，一个是运算符集合，且运算符在集合内
      {
        //
        // 因为符号被集合包含所以主要对比集合为主。
        //
        opt_t x1, x2;
        std::string y1, y2;
        std::pair<opt_t, opt_t> pp;
        pp = __on_symopt_optset_order(ip.first, ip.second);
        x1 = pp.first;
        y1 = pp.second;
        pp = __on_symopt_optset_order(jp.first, jp.second);
        x2 = pp.first;
        y2 = pp.second;

        set_relation_t rel = relation_optset(y1, y2);
        if (rel == kSet1Include2)
        {
          r = false;
        }
        else if (rel == kSet2Include1)
        {
          r = true;
        }
        else if ((rel == kSetNoneIntersect) || 
                 (rel == kSet1Equ2) || 
                 (rel == kSetIntersect))
        {
          // 对比两个集合的优先级
          int c = __cmp_priority(y1, y2);
          r = c == 1 ? true : false;
        }
      } break;
      case 4: // i,j其中一个是运算符，一个是运算符集合，且运算符不在集合内
      {
        //
        // 因为没有包含，这里无论y1,y2的关系如何，都以x1,x2的优先级作为对比。
        //
        // opt_t x1, x2;
        // std::string y1, y2;
        // std::pair<opt_t, opt_t> pp;
        // pp = __on_symopt_optset_order(ip.first, ip.second);
        // x1 = pp.first;
        // y1 = pp.second;
        // pp = __on_symopt_optset_order(jp.first, jp.second);
        // x2 = pp.first;
        // y2 = pp.second;

        // int c = cmp_operator_priority(x1, x2);
        // r = c == 1 ? true : false;
        r = si.second > sj.second ? true : false;
      } break;
      case 5: // i,j都是运算符集合，且相等
      {
        set_relation_t rel = relation_optset(ip.first, jp.first);
        if ((rel == kSet1Include2) || (rel == kSet1Equ2))
        {
          r = false;
        }
        else if (rel == kSet2Include1)
        {
          r = true;
        }
        else if ((rel == kSetNoneIntersect) || (rel == kSetIntersect))
        {
          r = si.second > sj.second ? true : false;
        }
      } break;
      case 6: // i,j都是运算符集合，且一个被一个包含
      {
        set_relation_t rel = relation_optset(ip.first, ip.second);
        std::string x = rel == kSet1Include2 ? ip.first : ip.second;
        rel = relation_optset(jp.first, jp.second);
        std::string y = rel == kSet1Include2 ? jp.first : jp.second;

        // 比较两个集合
        rel = relation_optset(x, y);
        if ((rel == kSet1Include2) || (rel == kSet1Equ2))
        {
          r = false;
        }
        else if (rel == kSet2Include1)
        {
          r = true;
        }
        else if ((rel == kSetNoneIntersect) || (rel == kSetIntersect))
        {
          r = si.second > sj.second ? true : false;
        }
      } break;
      case 7: // i,j都是运算符集合，且相交
      case 8: // i,j都是运算符集合，且无交集
      {
        r = si.second > sj.second ? true : false;
      } break;
      default:
      // 异常
        break;
      }
    }
    else
    {
      //
      // 处理模式不一致的地方
      //
#ifdef __DETAIL_CMP_MODE_NOT_MATCHED
      int im = si.first, jm = sj.first;
      if ((im == 1) || (jm == 1))
        r = __cmp_when_1(ip, jp, si, sj);
      else if ((im == 2) || (jm == 2))
        r = __cmp_when_2(ip, jp, si, sj);
      else if ((im == 3) || (jm == 3))
        r = __cmp_when_3(ip, jp, si, sj);
      else if ((im == 4) || (jm == 4))
        r = __cmp_when_4(ip, jp, si, sj);
      else if ((im == 5) || (jm == 5))
        r = __cmp_when_5(ip, jp, si, sj);
      else if ((im == 6) || (jm == 6))
        r = __cmp_when_6(ip, jp, si, sj);
      else if ((im == 7) || (jm == 7))
        r = __cmp_when_7(ip, jp, si, sj);
#else
      r = si.second > sj.second ? true : false;
#endif
    }
    return r;
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
    else if ((is_symopt(i) && !is_symopt(j)) || (!is_symopt(i) && is_symopt(j)))
    {
      bool i_is_symopt = is_symopt(i);
      std::string x, y;
      if (is_symopt(i))
      {
        x = i;
        y = j;
      }
      else
      {
        x = j;
        y = i;
      }
      if (in_optset(y, x))
      {
        return i_is_symopt ? true : false;
      }
      
      symopt_t sx;
      optset_t oy;
      if (find_symopt(x, sx) == false)
      {
        mysym_not_found_operator_exception("%s", x.c_str());
      }
      if (find_optset(y, oy) == false)
      {
        mysym_not_found_operator_set_exception("%s", y.c_str());
      }

      bool p = sx.priority < oy.average_priority;
      return p && i_is_symopt;
    }
    else 
    {
      // 两个都是optset
      set_relation_t rel = relation_optset(i, j);
      if (rel == kSet2Include1)
      {
        return true;
      }
      else if ((rel == kSet1Include2) || (rel == kSet1Equ2))
      {
        return false;
      }
      else if (rel == kSetNoneIntersect)
      {
        optset_t oi, oj;
        if (find_optset(i, oi) == false)
        {
          mysym_not_found_operator_set_exception("%s", i.c_str());
        }
        if (find_optset(j, oj) == false)
        {
          mysym_not_found_operator_set_exception("%s", j.c_str());
        }
        return oi.average_priority < oj.average_priority;
      }
      else if (rel == kSetIntersect)
      {
        opts_pair_t ds = difference_optset(i, j);
        double p1 = 0, p2 = 0;
        for (auto p : ds.first)
          p1 += opt_priority(p);
        for (auto p : ds.second)
          p2 += opt_priority(p);
        p1 /= ds.first.size();
        p2 /= ds.second.size();
        return p1 < p2;
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