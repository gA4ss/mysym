#include <mysym/mysym.h>

namespace mysym
{

  //
  // 规则库
  //
  static rule_library_t __rule_library;

  ///////////////////////////////////////////////////////////////////////
  void append_entry(opt_t opt, fptr_entry_t fentry)
  {
    __rule_library.entries[opt] = fentry;
  }

  void append_case(opt_t opt, optsign_t sign, fptr_execute_t fexecute)
  {
    __rule_library.cases[opt][sign] = fexecute;
  }

  bool find_entry(opt_t opt)
  {
    return __rule_library.entries.find(opt) != __rule_library.entries.end();
  }

  bool find_case(opt_t opt, optsign_t ops)
  {
    if (__rule_library.cases.find(opt) == __rule_library.cases.end())
      return false;
    if (__rule_library.cases[opt].find(ops) == __rule_library.cases[opt].end())
      return false;
    return true;
  }

  // t一定是单个运算符号
  // m可能是运算符号可能是运算符号集合
  static bool __match_opt(opt_t m, opt_t t)
  {
    if (is_symopt(m))
    {
      if (m == t)
        return true;
      else
        return false;
    }

    return in_optset(m, t);
  }

  bool meet_conditions(opt_t opt, const symbol_t &x, const symbol_t &y)
  {
    opt_t xo = kind(x), yo = kind(y);
    optsign_t xys = make_optsign(xo, yo);
    if (find_case(opt, xys) == true)
      return true;
    //
    // 遍历注册得运算符号集合
    //
    auto it = __rule_library.cases[opt].begin();
    for (; it != __rule_library.cases[opt].end(); it++)
    {
      optsign_t ops = it->first;
      optpair_t opp = split_optcase(ops);

      //
      // 判断
      //
      if (__match_opt(opp.first, xo) && __match_opt(opp.second, yo))
        return true;
    }
    return false;
  }

  symbol_t execute_entry(const symbol_t &x)
  {
    if (find_entry(kind(x)) == false)
      return undefined;
    return __rule_library.entries[kind(x)](x);
  }

  symbol_t execute_cases(opt_t opt, const symbol_t &x, const symbol_t &y)
  {
    if (meet_conditions(opt, x, y) == false)
      return undefined;
    optsign_t sign = make_optsign(kind(x), kind(y));
    return __rule_library.cases[opt][sign](x, y);
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

  std::string basic_optsets()
  {
    return "basic,const";
  }

  symbol_t default_entry(const symbol_t &x)
  {
    return x;
  }

  symbol_t default_execute(opt_t opt, const symbol_t &x, const symbol_t &y)
  {
    return just_make2(opt, x, y);
  }
} // namespace mysym