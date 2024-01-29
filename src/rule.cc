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

  bool find_single_case(opt_t opt, opt_t param, fptr_single_execute_t *fptr)
  {
    if (fptr)
      *fptr = nullptr;

    if (__rule_library.single_cases.find(opt) != __rule_library.single_cases.end())
    {
      if (__rule_library.single_cases[opt].find(param) != __rule_library.single_cases[opt].end())
      {
        if (fptr)
          *fptr = __rule_library.single_cases[opt][param];
        return true;
      }
    }
    return false;
  }

  bool find_case(opt_t opt, optsign_t ops, fptr_execute_t *fptr)
  {
    if (fptr)
      *fptr = nullptr;

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

  void append_single_case(opt_t opt, std::string param, fptr_single_execute_t fptr)
  {
    if (is_symopt(param))
    {
      __rule_library.single_cases[opt][param] = fptr;
    }
    else if (is_optset(param))
    {
      opts_t opts = expand_optset(param);
      for (auto so : opts)
      {
        __rule_library.single_cases[opt][so] = fptr;
      }
    }
    return;
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

  void register_preprocess(opt_t opt, fptr_preproccess_t fpreproccess)
  {
    __rule_library.preproccesses[opt] = fpreproccess;
  }

  void register_postprocess(opt_t opt, fptr_postproccess_t fpostproccess)
  {
    __rule_library.postproccesses[opt] = fpostproccess;
  }

  void register_case(opt_t opt, opt_t param, fptr_single_execute_t fexecute)
  {
    append_single_case(opt, param, fexecute);
  }

  void register_case(opt_t opt, optsign_t sign, fptr_execute_t fexecute)
  {
    //
    // 添加正序的case
    //
    append_case(opt, sign, fexecute);

    //
    // 添加逆序的case
    //
    optpair_t opp = split_optsign(sign);
    optsign_t rsign = make_optsign(opp.second, opp.first);
    append_case(opt, rsign, fexecute);
  }

  static bool __cmp_case(const rule_case_t &c1, const rule_case_t &c2)
  {
    return cmp_optsign(c1.first, c2.first);
  }

  void sort_case(opt_t opt)
  {
    //
    // 判断是否存在
    //
    if (__rule_library.cases.find(opt) == __rule_library.cases.end())
      return;

    //
    // 排序
    //
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

  static inline bool __preprocess(opt_t opt, const symbol_t &x, const symbol_t &y,
                                  symbol_t &z)
  {
    if (__rule_library.preproccesses.find(opt) != __rule_library.preproccesses.end())
    {
      fptr_preproccess_t preprocess = __rule_library.preproccesses[opt];
      if (preprocess)
        return preprocess(x, y, z);
    }
    z = gConstUDF;
    return false;
  }

  static inline symbol_t __postprocess(opt_t opt, const symbol_t &z)
  {
    if (__rule_library.postproccesses.find(opt) != __rule_library.postproccesses.end())
    {
      fptr_postproccess_t postprocess = __rule_library.postproccesses[opt];
      if (postprocess)
        return postprocess(z);
    }
    return z;
  }

  symbol_t execute_cases(opt_t opt, const symbol_t &x)
  {
    symbol_t y;
    if (__preprocess(opt, x, gConstUDF, y))
      return y;

    fptr_single_execute_t fptr = nullptr;
    if (find_single_case(opt, kind(x), &fptr))
    {
      y = fptr(x);
      return __postprocess(opt, y);
    }

    y = just_make1(opt, x);
    return __postprocess(opt, y);
  }

  //
  // 所有具体执行都会执行到这里
  //
  symbol_t execute_cases(opt_t opt, const symbol_t &x, const symbol_t &y)
  {

    //
    // 进行预处理
    //
    symbol_t z;
    if (__preprocess(opt, x, y, z))
      return z;
    //
    // 执行对应函数
    //
    optsign_t sign;
    if (__meet_conditions(opt, x, y, sign))
    {
      fptr_execute_t fptr = nullptr;
      if (find_case(opt, sign, &fptr))
      {
        z = fptr(x, y);
        return __postprocess(opt, z);
      }
    }

    z = just_make2(opt, x, y);
    return __postprocess(opt, z);
  }

  void init_rule()
  {
    register_atom_rule();
    register_cmp_rule();

    register_add_rule();
    register_sub_rule();
    register_mul_rule();
    register_div_rule();
    register_mod_rule();

    register_abs_rule();
    register_fact_rule();
    register_frac_rule();

    register_pow_rule();
    register_log_rule();

    register_sin_rule();
    register_cos_rule();
    register_tan_rule();
    register_cot_rule();
    register_sec_rule();
    register_csc_rule();

    register_arcsin_rule();
    register_arccos_rule();
    register_arctan_rule();
    register_arccot_rule();
    register_arcsec_rule();
    register_arccsc_rule();

    register_sinh_rule();
    register_cosh_rule();
    register_tanh_rule();
    register_coth_rule();
    register_sech_rule();
    register_csch_rule();

    register_arcsinh_rule();
    register_arccosh_rule();
    register_arctanh_rule();
    register_arccoth_rule();
    register_arcsech_rule();
    register_arccsch_rule();

    register_lnot_rule();
    register_land_rule();
    register_lor_rule();

    register_equ_rule();
    register_neq_rule();
    register_ge_rule();
    register_gt_rule();
    register_le_rule();
    register_lt_rule();
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