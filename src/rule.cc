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

  static void __register_add_rule()
  {
    register_rule(kOptAdd, __c_add_num_num, __e_add_num_num);
    register_rule(kOptAdd, __c_add_num_frac, __e_add_num_frac);
    register_rule(kOptAdd, __c_add_num_nature, __e_add_num_nature);
    register_rule(kOptAdd, __c_add_num_var, __e_add_num_var);
    register_rule(kOptAdd, __c_add_num_func, __e_add_num_func);

    register_rule(kOptAdd, __c_add_frac_frac, __e_add_frac_frac);
    register_rule(kOptAdd, __c_add_frac_nature, __e_add_frac_nature);


    register_rule(kOptAdd, __c_add_frac_var, __e_add_frac_var);
    register_rule(kOptAdd, __c_add_frac_func, __e_add_frac_func);

    register_rule(kOptAdd, __c_add_nature_nature, __e_add_nature_nature);
    register_rule(kOptAdd, __c_add_nature_var, __e_add_nature_var);

    register_rule(kOptAdd, __c_add_nature_func, __e_add_nature_func);
    register_rule(kOptAdd, __c_add_var_var, __e_add_var_var);

    register_rule(kOptAdd, __c_add_var_func, __e_add_var_func);
    register_rule(kOptAdd, __c_add_func_func, __e_add_func_func);

    register_rule(kOptAdd, __c_add, __e_add);
    register_rule(kOptAdd, __c_add_entry, __e_add_entry);
  }

  void init_rule()
  {
    __register_add_rule();
  }
} // namespace mysym