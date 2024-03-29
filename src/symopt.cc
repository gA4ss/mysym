#include <mysym/mysym.h>

namespace mysym
{
  typedef std::map<std::string, symopt_t> symopts_t;
  static symopts_t __symopts;

#define define_opt(opt, pri, ass, com, dis, ide, inv, invu, att, id) \
  __symopts[opt] = {opt, pri, ass, com, dis, ide, inv, invu, att, id}

  static void __define_func(opt_t o, bool con, int odev,
                            const symbol_t &per, const symbol_t &dod, const symbol_t &dov)
  {
    if (__symopts[o].attr == nullptr)
      __symopts[o].attr = std::make_shared<symopt_func_attr_t>();
    __symopts[o].attr->continuous = con;
    __symopts[o].attr->odevity = odev;
    __symopts[o].attr->period = per;
    __symopts[o].attr->dod = dod;
    __symopts[o].attr->dov = dov;
  }

  void init_symopt(){
#include "symopt.def"
#include "functions.def"
  }

  optid_t make_optid(std::string name)
  {
    std::hash<std::string> hash_opt_name;
    return hash_opt_name(name);
  }

  bool is_symopt(std::string name)
  {
    return __symopts.find(name) != __symopts.end();
  }

  bool find_symopt(std::string name, symopt_t &out)
  {
    if (__symopts.find(name) == __symopts.end())
      return false;
    out = __symopts[name];
    return true;
  }

  std::string opt_name(opt_t o)
  {
    if (__symopts.find(o) == __symopts.end())
      return "";
    return __symopts[o].opt;
  }

  int opt_priority(opt_t o)
  {
    if (__symopts.find(o) == __symopts.end())
      return -1;
    return __symopts[o].priority;
  }

  double opts_priority(const opts_t &opts)
  {
    double p = 0.0;
    for (auto it : opts)
    {
      p += opt_priority(it);
    }
    return p / opts.size();
  }

  bool opt_associative_law(opt_t o)
  {
    if (__symopts.find(o) == __symopts.end())
      return false;
    return __symopts[o].associative_law;
  }

  bool opt_commutative_law(opt_t o)
  {
    if (__symopts.find(o) == __symopts.end())
      return false;
    return __symopts[o].commutative_law;
  }

  bool opt_distributive_law(opt_t o)
  {
    if (__symopts.find(o) == __symopts.end())
      return false;
    return distributive_law(__symopts[o]);
  }

  symbol_t opt_identity(opt_t o)
  {
    symopt_t p;
    if (find_symopt(o, p) == false)
      return gConstUDF;
    return p.identity;
  }

  opt_t opt_inverse(opt_t o)
  {
    symopt_t p;
    if (find_symopt(o, p) == false)
      return kOptNone;
    return p.inverse;
  }

  int cmp_operator_priority(opt_t o1, opt_t o2)
  {
    if (__symopts[o1].priority < __symopts[o2].priority)
      return -1;
    else if (__symopts[o1].priority > __symopts[o2].priority)
      return 1;
    else
      return 0;
  }

  bool can_distributive(opt_t os, opt_t od)
  {
    if ((__symopts.find(os) == __symopts.end()) ||
        (__symopts.find(od) == __symopts.end()))
      return false;
    if (!distributive_law(__symopts[os]))
      return false;
    return (std::find(__symopts[os].distributives.begin(),
                      __symopts[os].distributives.end(), od) !=
            __symopts[os].distributives.end());
  }

  optid_t opt_id(opt_t o)
  {
    if (__symopts.find(o) == __symopts.end())
      return 0;
    return __symopts[o].id;
  }

  std::string symopts()
  {
    std::string res;
    for (auto it : __symopts)
    {
      res += it.first;
      res += ",";
    }
    // 弹出最后一个","
    if (!res.empty())
      res.pop_back();
    return res;
  }
} // namespace mysym