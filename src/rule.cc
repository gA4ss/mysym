#include <mysym/mysym.h>
#include "__misc.h"

namespace mysym
{

  //
  // 规则库
  //
  static rule_library_t __rule_library;
  rule_library_t &rule_library()
  {
    return __rule_library;
  }

  ///////////////////////////////////////////////////////////////////////
  void append_entry(opt_t opt, fptr_entry_t fentry)
  {
    __rule_library.entries[opt] = fentry;
  }

  void append_case(opt_t opt, optsign_t sign, fptr_execute_t fexecute)
  {
    for (auto it = __rule_library.cases[opt].begin();
         it != __rule_library.cases[opt].end();
         it++)
    {
      if (it->first == sign)
      {
        it->second = fexecute;
        return;
      }
    }

    // 更新表
    __rule_library.cases[opt].push_back({sign, fexecute});
    __rule_library.casetbl[opt][sign] = __rule_library.cases[opt].size() - 1;
  }

  void register_case(opt_t opt, optsign_t sign, fptr_execute_t fexecute)
  {
    // __rule_library.cases[opt][sign] = fexecute;
    append_case(opt, sign, fexecute);
    // 替换两个位置
    optpair_t opp = split_optsign(sign);
    optsign_t rsign = make_optsign(opp.second, opp.first);
    // __rule_library.cases[opt][rsign] = fexecute;
    append_case(opt, rsign, fexecute);
  }

  static bool __cmp_case(const rule_case_t &c1, const rule_case_t &c2)
  {
    return cmp_optsign(c1.first, c2.first);
  }

  void sort_case(opt_t opt)
  {
    if (find_entry(opt) == false)
      return;
    std::sort(__rule_library.cases[opt].begin(), 
              __rule_library.cases[opt].end(),
              __cmp_case);

    //
    // 更新索引
    //
    size_t i = 0;
    for (auto it = __rule_library.cases[opt].begin();
         it != __rule_library.cases[opt].end();
         it++)
    {
      __rule_library.casetbl[opt][it->first] = i;
      ++i;
    }
  }

  bool find_entry(opt_t opt)
  {
    return __rule_library.entries.find(opt) != __rule_library.entries.end();
  }

  bool find_case(opt_t opt, optsign_t ops, fptr_execute_t *fptr)
  {
    if (fptr) *fptr = nullptr;
    if (__rule_library.casetbl.find(opt) == __rule_library.casetbl.end())
      return false;
    if (__rule_library.casetbl[opt].find(ops) == __rule_library.casetbl[opt].end())
      return false;
    
    if (fptr)
    {
      size_t k = __rule_library.casetbl[opt][ops];
      *fptr = __rule_library.cases[opt][k].second;
    }
    return true;
  }

  // t一定是单个运算符号
  // m可能是运算符号可能是运算符号集合
  static bool __match_opt(opt_t m, opt_t t)
  {
    mysym_assert(is_symopt(t), "%s is not symopt.", t.c_str());

    if (is_symopt(m))
    {
      if (m == t)
        return true;
      else
        return false;
    }

    mysym_assert(is_optset(m), "%s is not optset.", m.c_str());
    return in_optset(m, t);
  }

  static bool __meet_conditions(opt_t opt, const symbol_t &x, const symbol_t &y, 
                                optsign_t &z)
  {
    //
    // 首先使用符号本身的运算符进行合成，查看是否可以找到匹配
    // 如果找不到则进入遍历依次匹配
    //
    opt_t xo = kind(x), yo = kind(y);
    optsign_t xys = make_optsign(xo, yo);
    if (find_case(opt, xys) == true)
    {
      z = xys;
      return true;
    }

    //
    // 遍历注册得运算符号集合
    //
    auto it = __rule_library.cases[opt].begin();
    for (; it != __rule_library.cases[opt].end(); it++)
    {
      optsign_t ops = it->first;
      optpair_t opp = split_optsign(ops);

      //
      // 判断
      //
      if (__match_opt(opp.first, xo) && __match_opt(opp.second, yo))
      {
        z = ops;
        return true;
      }
    }
    return false;
  }

  symbol_t execute_entry(const symbol_t &x)
  {
    if (find_entry(kind(x)) == false)
      return x;
    return __rule_library.entries[kind(x)](x);
  }

  symbol_t execute_cases(opt_t opt, const symbol_t &x, const symbol_t &y)
  {
    optsign_t sign;
    if (__meet_conditions(opt, x, y, sign) == false)
      return just_make2(opt, x, y);
    fptr_execute_t fptr = nullptr;
    if (find_case(opt, sign, &fptr))
    {
      return fptr(x, y);
    }
    return just_make2(opt, x, y);
  }

  void apply_rule(symbol_t &x)
  {
    x = execute_entry(x);
  }

  void init_rule()
  {
    register_atom_rule();
    register_add_rule();
    register_cmp_rule();
  }

  symbol_t default_entry(const symbol_t &x)
  {
    return x;
  }

  symbol_t default_execute(const symbol_t &x, const symbol_t &y)
  {
    return just_make2(kOptNone, x, y);
  }

  void default_cases(opt_t opt, std::string ops)
  {
    optcase_t cases = generate_optcase(ops);
    for (auto it = cases.begin(); it != cases.end(); it++)
    {
      append_case(opt, *it, default_execute);
    }
  }

  void append_optcase_string(std::string &ops, const std::string op)
  {
    std::vector<std::string> l = split_string(op);
    if (l.empty())
      return;

    for (auto it = l.begin(); it != l.end(); it++)
    {
      if (ops.find(*it) == std::string::npos)
      {
        if (!ops.empty())
          ops += ",";
        ops += *it;
      }
    }
  }

  void append_optcase_string(std::string &ops, const std::vector<std::string> opl)
  {
    if (opl.empty())
      return;

    for (auto it = opl.begin(); it != opl.end(); it++)
    {
      if (ops.find(*it) == std::string::npos)
      {
        if (!ops.empty())
          ops += ",";
        ops += *it;
      }
    }
  }
} // namespace mysym