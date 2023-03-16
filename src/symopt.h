#ifndef MYSYM_SYMOPT_H_
#define MYSYM_SYMOPT_H_

namespace mysym
{

#define kOptNone "none"

#define kOptAdd "+"
#define kOptMul "*"

#define kOptEqu "="
#define kOptNotEqu "!="
#define kOptLT "<"
#define kOptLE "<="
#define kOptGT ">"
#define kOptGE ">="

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
#define kOptNumber "%"
#define kOptFrac "/"
#define kOptConstE "e"
#define kOptConstPI "pi"
#define kOptConstInf "inf"
#define kOptConstNegInf "-inf"

// #define kOptInteger "integer"
// #define kOptFloat "float"

  typedef std::string opt_t;

  typedef struct __symopt_t
  {
    opt_t opt;
    int prio;
    bool sorted;
  } symopt_t;

#define is_symopt(o1, o2) ((o1) == (o2))

  std::string opt_name(opt_t o);
  int opt_prio(opt_t o);
  bool opt_sorted(opt_t o);
  int cmp_operator_priority(opt_t o1, opt_t o2);

  typedef struct __optset_t
  {
    std::string name;
    std::map<std::string, symopt_t> items;
  } optset_t;

  typedef std::vector<std::string> optnames_t;

  optset_t create_set(std::string setname, std::string optnames);
  optset_t create_set(std::string setname, optnames_t optnames);
  optset_t create_set_include_sets(std::string setname, std::string setnames);
  optset_t create_set_exclude_sets(std::string setname, std::string setnames);
  bool in_set(std::string setname, std::string optname);
  optnames_t in_set(std::string setname, optnames_t optnames);
  std::string symopts();
  void init_symopt();
  void init_symset();

#define is_none(o) (o == kOptNone)
#define is_und(o) is_none(o)
#define is_add(o) (o == kOptAdd)
#define is_mul(o) (o == kOptMul)
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

#define is_opt(o) (in_set("opt", o))
#define is_basic(o) (in_set("basic", o))
#define is_sym(o) (in_set("sym", o))
#define is_const(o) (in_set("const", o))
#define is_nature(o) (in_set("nature", o))
#define is_basic_func(o) (in_set("basicf", o))
#define is_trigo(o) (in_set("trigo", o))
#define is_inv_trigo(o) (in_set("itrigo", o))
#define is_hyper(o) (in_set("hyper", o))
#define is_inv_hyper(o) (in_set("ihyper", o))
#define is_func(o) (in_set("func", o))
#define is_2ps_func(o) (in_set("func2p", o))

} // namespace mysym

#endif // MYSYM_SYMOPT_H_