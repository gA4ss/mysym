#ifndef MYSYM_SYMOPT_H_
#define MYSYM_SYMOPT_H_

#include <mysym/set.hpp>
#include <unordered_set>

namespace mysym
{
  typedef std::string opt_t;
  typedef std::vector<opt_t> opts_t;
  typedef std::pair<opts_t, opts_t> opts_pair_t;
  typedef struct __symopt_attribute_t
  {
    bool continuous;        // 是否是连续的
    // opt_t inverse_opt;   // 逆操作
    // std::string unit1;   // 单位元
  } symopt_attr_t;

  typedef struct __symopt_t
  {
    opt_t opt;
    int priority;                     // 优先级
    bool associative_law;             // 结合律
    bool commutative_law;             // 交换律
    std::vector<opt_t> distributives; // 分配针对操作
    std::string unit1;                // 单位
    symopt_attr_t attr;               // 属性
  } symopt_t;
#define distributive_law(s) (s.distributives.size() != 0)

  bool is_symopt(std::string name);
  bool find_symopt(std::string name, symopt_t &out);
  std::string opt_name(opt_t o);
  int opt_priority(opt_t o);
  double opts_priority(const opts_t &opts);
  bool opt_associative_law(opt_t o);
  bool opt_commutative_law(opt_t o);
  bool opt_distributive_law(opt_t o);
  bool opt_continuous(opt_t o);
  int cmp_operator_priority(opt_t o1, opt_t o2);
  bool can_distributive(opt_t os, opt_t od);
  std::string symopts();

  typedef set_t<symopt_t> symopt_set_t;
  typedef std::pair<symopt_set_t, symopt_set_t> symopt_set_pair_t;

  typedef struct __optset_t
  {
    std::string name;                         // 名称
    symopt_set_t items;                       // 符号集合
    std::unordered_set<int> priority_array;   // 优先级队列
    int max_priority;                         // 最大优先级
    int min_priority;                         // 最小优先级
    double average_priority;                  // 平均优先级
  } optset_t;

  size_t size(optset_t os);
  size_t size_optset(std::string setname);
  bool is_optset(std::string name);
  bool as_symopt(std::string name);
  bool find_optset(std::string name, optset_t &out);
  optset_t create_optset(std::string setname, std::string names);
  optset_t create_optset(std::string setname, std::vector<std::string> names);
  optset_t create_optset_exclude(std::string setname, std::string setnames);
  bool in_optset(std::string setname, std::string optname);
  bool as_symopt(std::string name);
  int optset_priority(std::string name);
  double auto_priority(std::string name);
  opts_t in_optset(std::string setname, opts_t optnames);
  opts_t expand_optset(const optset_t& s);
  opts_t expand_optset(std::string setname);
  opts_t intersection_optset(std::string s1, std::string s2);
  opts_t union_optset(std::string s1, std::string s2);
  opts_t complementary_optset(std::string s, std::string i);
  opts_pair_t difference_optset(std::string s1, std::string s2);
  set_relation_t relation_optset(std::string s1, std::string s2);
  std::string optsets();
  void init_symopt();
  void init_symset();

#define kOptAdd "+"
#define kOptSub "-"
#define kOptMul "*"
#define kOptDiv "/"

#define kOptEqu "="
#define kOptNotEqu "!="
#define kOptLT "<"
#define kOptLE "<="
#define kOptGT ">"
#define kOptGE ">="

#define kOptCmp "cmp"
#define kOptPow "^"
#define kOptLog "log"
#define kOptFact "!"
#define kOptAbs "abs"
#define kOptMod "mod"

#define kOptSin "sin"
#define kOptCos "cos"
#define kOptTan "tan"
#define kOptCot "cot"
#define kOptSec "sec"
#define kOptCsc "csc"

#define kOptArcSin "arcsin"
#define kOptArcCos "arccos"
#define kOptArcTan "arctan"
#define kOptArcCot "arccot"
#define kOptArcSec "arcsec"
#define kOptArcCsc "arccsc"

#define kOptSinh "sinh"
#define kOptCosh "cosh"
#define kOptTanh "tanh"
#define kOptCoth "coth"
#define kOptSech "sech"
#define kOptCsch "csch"

#define kOptArcSinh "arcsinh"
#define kOptArcCosh "arccosh"
#define kOptArcTanh "arctanh"
#define kOptArcCoth "arccoth"
#define kOptArcSech "arcsech"
#define kOptArcCsch "arccsch"

#define kOptVariate "$"
#define kOptConstE "e"
#define kOptConstPI "pi"
#define kOptConstInf "inf"
#define kOptConstNegInf "-inf"
#define kOptFrac "//"
#define kOptNumber "%"
#define kOptNone "none"

#define is_none(o) (o == kOptNone)
#define is_und(o) is_none(o)
#define is_add(o) (o == kOptAdd)
#define is_sub(o) (o == kOptSub)
#define is_mul(o) (o == kOptMul)
#define is_div(o) (o == kOptDiv)
#define is_pow(o) (o == kOptPow)
#define is_log(o) (o == kOptLog)
#define is_fact(o) (o == kOptFact)
#define is_abs(o) (o == kOptAbs)
#define is_mod(o) (o == kOptMod)
#define is_var(o) (o == kOptVariate)
#define is_num(o) (o == kOptNumber)
#define is_int(o) is_num(o)
#define is_flt(o) is_num(o)
#define is_frac(o) (o == kOptFrac)
#define is_e(o) (o == kOptConstE)
#define is_pi(o) (o == kOptConstPI)
#define is_inf(o) (o == kOptConstInf)
#define is_neg_inf(o) (o == kOptConstNegInf)

#define is_all(o) (in_optset("all", o))
#define is_opt(o) (in_optset("opt", o))
#define is_basic(o) (in_optset("basic", o))
#define is_atom(o) (in_optset("atom", o))
#define is_sym(o) (in_optset("sym", o))
#define is_const(o) (in_optset("const", o))
#define is_nature(o) (in_optset("nature", o))
#define is_basic_func(o) (in_optset("basicf", o))
#define is_trigo(o) (in_optset("trigo", o))
#define is_inv_trigo(o) (in_optset("itrigo", o))
#define is_hyper(o) (in_optset("hyper", o))
#define is_inv_hyper(o) (in_optset("ihyper", o))
#define is_func(o) (in_optset("func", o))
#define is_2ps_func(o) (in_optset("func2p", o))

} // namespace mysym

#endif // MYSYM_SYMOPT_H_