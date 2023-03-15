#include <mysym/mysym.h>

namespace mysym
{

  //
  // 规则库
  //
  static rule_library_t __rule_library;

  void register_rule(opt_t opt, fptr_condition_s_t fcondition, fptr_execute_s_t fexecute)
  {
    if (__rule_library.rs.find(opt) == __rule_library.rs.end())
    {
      __rule_library.rs[opt] = {{fcondition, fexecute}};
    }
    else
    {
      __rule_library.rs[opt].push_back({fcondition, fexecute});
    }
  }

  void register_rule(opt_t opt, fptr_condition_d_t fcondition, fptr_execute_d_t fexecute)
  {
    if (__rule_library.rd.find(opt) == __rule_library.rd.end())
    {
      __rule_library.rd[opt] = {{fcondition, fexecute}};
    }
    else
    {
      __rule_library.rd[opt].push_back({fcondition, fexecute});
    }
  }

  bool find_rule_table_s(opt_t opt, rule_table_s_t &tab)
  {
    if (__rule_library.rs.find(opt) == __rule_library.rs.end())
      return false;
    tab = __rule_library.rs[opt];
    return true;
  }
  bool find_rule_table_d(opt_t opt, rule_table_d_t &tab)
  {
    if (__rule_library.rd.find(opt) == __rule_library.rd.end())
      return false;
    tab = __rule_library.rd[opt];
    return true;
  }

  bool is_empty(const rule_table_s_t &tab)
  {
    return tab.empty();
  }
  bool is_empty(const rule_table_d_t &tab)
  {
    return tab.empty();
  }

  symbol_t apply_rule_table(const rule_table_s_t &r, const symbol_t &x)
  {
    for (auto it = r.begin(); it != r.end(); it++)
    {
      if (it->first(x))
        return it->second(x);
    }
    return undefined;
  }

  symbol_t apply_rule_table(const rule_table_d_t &r, const symbol_t &x, const symbol_t &y)
  {
    for (auto it = r.begin(); it != r.end(); it++)
    {
      if (it->first(x, y))
        return it->second(x, y);
    }
    return undefined;
  }

  // static symbol_t __execute_opt_rule(opt_t o, const symbol_t &x, const symbol_t &y)
  // {
  //   if (r.rd.find(o) == r.rd.end())
  //     return undefined;

  //   symbol_t _x = execute_opt_rule(o, x);
  //   symbol_t _y = execute_opt_rule(o, y);
  //   return apply_rule_table(o, _x, _y);
  // }

  symbol_t apply_rule(const symbol_t &x)
  {
    opt_t o = x.opt;
    if (__rule_library.rs.find(o) == __rule_library.rs.end())
      return undefined;
    return apply_rule_table(__rule_library.rs[o], x);
  }

#include "__rule.h"
  void init_rule()
  {
    // register_rule();
  }
} // namespace mysym