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

  //////////////////////////////////////////////////////////////////////////////////////////

  symbol_t execute_rule_table(const rule_table_s_t &r, const symbol_t &x)
  {
    for (auto it = r.begin(); it != r.end(); it++)
    {
      if (it->first(x))
        return it->second(x);
    }
    return undefined;
  }

  symbol_t execute_rule_table(opt_t opt, const symbol_t &x)
  {
    rule_table_s_t tab;
    if (!find_rule_table_s(opt, tab))
      return undefined;
    return execute_rule_table(tab, x);
  }

  symbol_t execute_rule_table(const rule_table_d_t &r, const symbol_t &x, const symbol_t &y)
  {
    for (auto it = r.begin(); it != r.end(); it++)
    {
      if (it->first(x, y))
        return it->second(x, y);
    }
    return undefined;
  }

  symbol_t execute_rule_table(opt_t opt, const symbol_t &x, const symbol_t &y)
  {
    rule_table_d_t tab;
    if (!find_rule_table_d(opt, tab))
      return undefined;
    return execute_rule_table(tab, x, y);
  }

  void apply_rule(symbol_t &x)
  {
    x = execute_rule_table(x.opt, x);
  }

  static bool __c_atom_entry(const symbol_t &x)
  {
    return is_atom(kind(x));
  }
  static symbol_t __e_atom_entry(const symbol_t &x)
  {
    return x;
  }

  void register_atom_rule()
  {
    register_rule(kOptVariate, __c_atom_entry, __e_atom_entry);
    register_rule(kOptNumber, __c_atom_entry, __e_atom_entry);
    register_rule(kOptFrac, __c_atom_entry, __e_atom_entry);
    register_rule(kOptConstE, __c_atom_entry, __e_atom_entry);
    register_rule(kOptConstPI, __c_atom_entry, __e_atom_entry);
    register_rule(kOptConstInf, __c_atom_entry, __e_atom_entry);
    register_rule(kOptConstNegInf, __c_atom_entry, __e_atom_entry);
  }

  void init_rule()
  {
    register_atom_rule();
    register_add_rule();
    register_cmp_rule();
  }
} // namespace mysym