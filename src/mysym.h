#ifndef MYSYM_H_
#define MYSYM_H_

#include <cmath>
#include <cfloat>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

#include <mympz/mympz.h>
#include <mympf/mympf.h>
#include <mynum/mynum.h>

#include <mysym/compile.h>
#include <mysym/exception.h>
#include <mysym/debug.h>
#include <mysym/symbol.h>

namespace mysym
{
  // typedef mympz::bignum_t symnum_t;
  typedef mympz::bignum_t integer_t;
  typedef mympf::float_t float_t;
  typedef mynum::number_t number_t;
  typedef long double real_t;
  typedef long long int long_t;

  //
  // 使用符号严格限定的几个类型
  //
  typedef symbol_t var_t;
  typedef symbol_t num_t;
  typedef symbol_t int_t;
  typedef symbol_t flt_t;

  bool symbol_is_integer(const num_t &x);
  bool symbol_is_real(const num_t &x);
#define symbol_is_number(x) (symbol_is_integer(x) || symbol_is_real(x))

#define kSignPositive true
#define kSignNegative false
  bool sign(const symbol_t &x);
  symbol_t opposite(const symbol_t &x);

  //
  // 列表
  //
  typedef symbol_items_t list_t;

  size_t size(const list_t &l);
  bool find(const list_t &l, const symbol_t &s);
  bool match(const list_t &l, const symbol_t &s);
  void append(list_t &l, const symbol_t &s, bool found = false);
  void append(list_t &dl, const list_t &sl, bool found = false);
  void clear(list_t &l);

  //
  // 知识库
  // 用于存储一些全局公共变量的数据
  //
  typedef struct __config_t
  {
    // 遇到浮点数与分数相加是否运算，默认不运算，保留两个符号。
    bool is_compute_frac_float;
    // 乘法遇到多项式乘以某个符号时候，不进行展开。
    bool is_mul_polynomial_not_expand;
  } config_t;
  typedef struct __library_t
  {
    __library_t();
    config_t config;
  } library_t;
  typedef std::shared_ptr<library_t> library_ptr_t;

  extern library_ptr_t __plibrary;
#define plibrary() __plibrary
  library_ptr_t init_library();

#define make_symbol_ptr() std::make_shared<symbol_t>()
#define get_opt(s) (s).opt
#define symbol_size(s) (s.items.size())
#define is_single(s) (!symbol_size(s))
#define is_unary_operation(s) (is_opt(s.opt) && (symbol_size(s) == 1))

  void init_global();
  void init();
  symbol_t create(opt_t opt, std::string literal = "");
  symbol_t create(opt_t opt, const symbol_items_t &items);
  symbol_t create_symbol(std::string literal);

  symbol_t make(opt_t opt, const symbol_t &s, bool nas = false);
  symbol_t make(opt_t opt, const symbol_t &s1, const symbol_t &s2, bool nas = false);
#define just_make1(opt, s1) make(opt, s1, true)
#define just_make2(opt, s1, s2) make(opt, s1, s2, true)

  symbol_t make(opt_t opt, std::string s, bool nas = false);
  symbol_t make(opt_t opt, std::string s1, std::string s2, bool nas = false);

  symbol_t make(opt_t opt, std::string s1, const symbol_t &s2, bool nas = false);
  symbol_t make(opt_t opt, const symbol_t &s1, std::string s2, bool nas = false);

#define create_opt(opt) create(opt)
#define create_none() create(kOptNone)
#define create_var(literal) create(kOptVariate, literal)
#define create_int(literal) create(kOptNumber, literal)
#define create_flt(literal) create(kOptNumber, literal)
#define create_sym(literal) create_symbol(literal)
#define create_mul_items(items) create(kOptMul, items)
#define create_add_items(items) create(kOptAdd, items)
#define undefined create_none()

  void copy(const symbol_t &s, symbol_t &d);

#define kind(s) get_opt(s)
#define number_of_operands(s) symbol_size(s)
  symbol_t operand(const symbol_t &s, size_t i);
  symbol_t base(const symbol_t &s);
  symbol_t exponent(const symbol_t &s);
  symbol_t term(const symbol_t &s);
  list_t terms(const symbol_t &s);
  symbol_t constant(const symbol_t &s);
#define antilog(s) exponent(s)
  symbol_t expansion(const symbol_t &s);

  bool match(const symbol_t &s1, const symbol_t &s2);
  bool match_in(const symbol_t &s1, const symbol_t &s2);

  int compare(const symbol_t &s1, const symbol_t &s2);
  void merge(symbol_t &x);
  void sort(symbol_t &s, bool reverse = false);
  void automatic_simplify(symbol_t &s);

  list_t complete_sub_expressions(const symbol_t &s, bool found = false);
  bool free_of(const symbol_t &s, const symbol_t &u);
  bool free_of(const symbol_t &s, const list_t &xs);
  list_t variables(const symbol_t &s);
  list_t abstract_variables(const symbol_t &s);
  list_t constants(const symbol_t &s);
  list_t integers(const symbol_t &s);
  list_t reals(const symbol_t &s);
  list_t fractions(const symbol_t &s);
  list_t natures(const symbol_t &s);
  list_t functions(const symbol_t &s);
  list_t pows(const symbol_t &s);
  list_t logs(const symbol_t &s);
  list_t abses(const symbol_t &s);

#define is_undefined(s) is_none(kind(s))
  bool is_monomial(const symbol_t &s, const symbol_t &x);
  bool is_monomial(const symbol_t &s, const list_t &xs);
  bool is_polynomial(const symbol_t &s, const symbol_t &x);
  bool is_polynomial(const symbol_t &s, const list_t &xs);

  //
  // 多项式运算
  //
  int_t degree(const symbol_t &s);
  int_t degree(const symbol_t &s, const symbol_t &x);
  int_t degree(const symbol_t &s, const list_t &xs);
  list_t coefficients(const symbol_t &s);
  int_t coefficient(const symbol_t &s, const symbol_t &x, const int_t &d);
  int_t leading_coefficient(const symbol_t &s, const symbol_t &x);

  long_t next_prime(int i);
  // typedef long long int exponent_t;
  // typedef symbol_t monomial_t;
  // typedef std::queue<symbol_t> polynomial_t;
  // polynomial_t create_polynomial(const list_t& l);

  //
  // map运算
  //
  typedef symbol_t (*fptr_map_t)(const symbol_t &);
  symbol_t map(fptr_map_t fmap, const symbol_t &s);
  symbol_t map(const symbol_t &u, const symbol_t &s, opt_t o = kOptNone, bool ex = false);

  //
  // 迭代运算
  //
  typedef symbol_t (*fptr_iteration_t)(const symbol_t &, const symbol_t &);
  symbol_t iterate(fptr_iteration_t fptr, const list_t &s);
  symbol_t iterate(opt_t opt, const list_t &s);

  //
  // 分数运算
  //
  symbol_t numerator(const symbol_t &s);
  symbol_t denominator(const symbol_t &s);
  symbol_t frac_to_prod(const symbol_t &s);
  symbol_t frac_to_num(const symbol_t &s);
  symbol_t num_to_frac(const symbol_t &s);
  mynum::fraction_t frac_to_mynum_fraction(const symbol_t &s);
  symbol_t mynum_fraction_to_frac(const mynum::fraction_t &f);
  symbol_t compute_frac_num(opt_t opt, const symbol_t &x, const symbol_t &y);
  symbol_t compute_frac_frac(opt_t opt, const symbol_t &x, const symbol_t &y);

  //
  // 数运算
  //
  symbol_t number_to_symbol(const number_t &f);
  number_t symbol_to_number(const symbol_t &s);

  //
  // 规则表
  //
  // 运算符匹配情况
  typedef std::string optsign_t;
  typedef std::vector<optsign_t> optcase_t;
  typedef std::pair<opt_t, opt_t> optpair_t;
  bool is_optsign(optsign_t sign);
  optsign_t make_optsign(opt_t opt1, opt_t opt2);
  optsign_t make_optsign_any(opt_t opt);
  optsign_t make_optsign_exclude(opt_t opt);
  optpair_t split_optsign(optsign_t sign);
  bool cmp_optsign(const optsign_t &i, const optsign_t &j);
  optcase_t generate_optcase(std::string ops);

  // 条件-执行表
  typedef bool (*fptr_condition_t)(opt_t, const symbol_t &, const symbol_t &);
  typedef bool (*fptr_preproccess_t)(const symbol_t &, const symbol_t &, symbol_t &);
  typedef symbol_t (*fptr_single_execute_t)(const symbol_t &);
  typedef symbol_t (*fptr_execute_t)(const symbol_t &, const symbol_t &);
  typedef symbol_t (*fptr_postproccess_t)(const symbol_t &);
  // typedef struct __cmp_rule_table_t
  // {
  //   bool operator()(const optsign_t &i, const optsign_t &j) const
  //   {
  //     return cmp_optsign(i, j);
  //   }
  // } cmp_rule_table_t;
  // typedef std::map<optsign_t, fptr_execute_t, cmp_rule_table_t> rule_table_t;
  typedef std::unordered_map<opt_t, fptr_single_execute_t> rule_single_table_t;
  typedef std::pair<optsign_t, fptr_execute_t> rule_case_t;
  typedef std::vector<rule_case_t> rule_table_t;
  typedef std::unordered_map<optsign_t, size_t> rule_table_index_t;
  typedef std::unordered_map<opt_t, rule_table_index_t> rule_case_query_t;
  // 条件执行项目
  typedef std::unordered_map<opt_t, fptr_preproccess_t> rule_preproccess_t;
  typedef std::unordered_map<opt_t, fptr_postproccess_t> rule_postproccess_t;
  typedef std::unordered_map<opt_t, rule_single_table_t> rule_single_object_t;
  typedef std::unordered_map<opt_t, rule_table_t> rule_object_t;

  typedef struct __rule_library_t
  {
    rule_preproccess_t preproccesses;
    rule_postproccess_t postproccesses;
    rule_single_object_t single_cases;
    rule_object_t cases;
    rule_case_query_t casetbl;
  } rule_library_t;
  rule_library_t &rule_library();

  void register_atom_rule();
  void register_cmp_rule();

  void register_add_rule();
  void register_sub_rule();
  void register_mul_rule();
  void register_div_rule();
  void register_mod_rule();

  void register_abs_rule();
  void register_fact_rule();
  void register_frac_rule();

  void register_pow_rule();
  void register_log_rule();

  void register_sin_rule();
  void register_cos_rule();
  void register_tan_rule();
  void register_cot_rule();
  void register_sec_rule();
  void register_csc_rule();

  void register_arcsin_rule();
  void register_arccos_rule();
  void register_arctan_rule();
  void register_arccot_rule();
  void register_arcsec_rule();
  void register_arccsc_rule();

  void register_sinh_rule();
  void register_cosh_rule();
  void register_tanh_rule();
  void register_coth_rule();
  void register_sech_rule();
  void register_csch_rule();

  void register_arcsinh_rule();
  void register_arccosh_rule();
  void register_arctanh_rule();
  void register_arccoth_rule();
  void register_arcsech_rule();
  void register_arccsch_rule();

  void register_lnot_rule();
  void register_land_rule();
  void register_lor_rule();

  void register_equ_rule();
  void register_neq_rule();
  void register_ge_rule();
  void register_gt_rule();
  void register_le_rule();
  void register_lt_rule();

  void init_rule();

  bool find_single_case(opt_t opt, opt_t param, fptr_single_execute_t *fptr = nullptr);
  bool find_case(opt_t opt, optsign_t ops, fptr_execute_t *fptr = nullptr);
  void append_single_case(opt_t opt, std::string param, fptr_single_execute_t fptr);
  void append_case(opt_t opt, optsign_t sign, fptr_execute_t fexecute);
  void register_preprocess(opt_t opt, fptr_preproccess_t fpreproccess);
  void register_postprocess(opt_t opt, fptr_postproccess_t fpostproccess);
  void register_case(opt_t opt, opt_t param, fptr_single_execute_t fexecute);
  void register_case(opt_t opt, optsign_t sign, fptr_execute_t fexecute);
  void sort_case(opt_t opt);
  symbol_t execute_cases(opt_t opt, const symbol_t &x);
  symbol_t execute_cases(opt_t opt, const symbol_t &x, const symbol_t &y);
  void append_optcase_string(std::string &ops, const std::string op);
  void append_optcase_string(std::string &ops, const std::vector<std::string> opl);

  // //
  // // 基础运算律
  // //
  // void apply_associative_law(symbol_t &x);
  // void apply_commutative_law(symbol_t &x);
  // void apply_distributive_law(symbol_t &x);
  // void combine_like_terms(symbol_t &x);
  // void format(symbol_t &x);
  // void play(symbol_t &x);
  // void apply_basic_rule(symbol_t &x);

  // 因子运算
  symbol_t gcd(const symbol_t &x);
  symbol_t gcd(const symbol_t &x, symbol_t &l);
  symbol_t gcd(const list_t &s);
  symbol_t gcd(const list_t &s, list_t &l);
  symbol_t lcm(const symbol_t &x);
  symbol_t lcm(const list_t &s);
  list_t extend_euclid(const list_t &s);

  //
  // 符号运算符
  //
  typedef symbol_t (*fptr_single_operator_t)(const symbol_t &);
  typedef symbol_t (*fptr_operator_t)(const symbol_t &, const symbol_t &);

  symbol_t add(const symbol_t &x, const symbol_t &y);
  symbol_t sub(const symbol_t &x, const symbol_t &y);
  symbol_t mul(const symbol_t &x, const symbol_t &y);
  symbol_t div(const symbol_t &x, const symbol_t &y);
  symbol_t lnot(const symbol_t &x);
  symbol_t land(const symbol_t &x, const symbol_t &y);
  symbol_t lor(const symbol_t &x, const symbol_t &y);
  symbol_t equ(const symbol_t &x, const symbol_t &y);
  symbol_t neq(const symbol_t &x, const symbol_t &y);
  symbol_t lt(const symbol_t &x, const symbol_t &y);
  symbol_t le(const symbol_t &x, const symbol_t &y);
  symbol_t gt(const symbol_t &x, const symbol_t &y);
  symbol_t ge(const symbol_t &x, const symbol_t &y);
  symbol_t cmp(const symbol_t &x, const symbol_t &y);
  symbol_t abs(const symbol_t &x);
  symbol_t fact(const symbol_t &x);
  symbol_t frac(const symbol_t &x, const symbol_t &y);
  symbol_t pow(const symbol_t &x, const symbol_t &y);
  symbol_t log(const symbol_t &x, const symbol_t &y);
  symbol_t mod(const symbol_t &x, const symbol_t &y);
  symbol_t sin(const symbol_t &x);
  symbol_t cos(const symbol_t &x);
  symbol_t tan(const symbol_t &x);
  symbol_t cot(const symbol_t &x);
  symbol_t sec(const symbol_t &x);
  symbol_t csc(const symbol_t &x);
  symbol_t arcsin(const symbol_t &x);
  symbol_t arccos(const symbol_t &x);
  symbol_t arctan(const symbol_t &x);
  symbol_t arccot(const symbol_t &x);
  symbol_t arcsec(const symbol_t &x);
  symbol_t arccsc(const symbol_t &x);
  symbol_t sinh(const symbol_t &x);
  symbol_t cosh(const symbol_t &x);
  symbol_t tanh(const symbol_t &x);
  symbol_t coth(const symbol_t &x);
  symbol_t sech(const symbol_t &x);
  symbol_t csch(const symbol_t &x);
  symbol_t arcsinh(const symbol_t &x);
  symbol_t arccosh(const symbol_t &x);
  symbol_t arctanh(const symbol_t &x);
  symbol_t arccoth(const symbol_t &x);
  symbol_t arcsech(const symbol_t &x);
  symbol_t arccsch(const symbol_t &x);

  //
  // 调用符号
  //
  symbol_t call_operator(opt_t opt, const symbol_t &x);
  symbol_t call_operator(opt_t opt, const symbol_t &x, const symbol_t &y);
  fptr_single_operator_t get_single_operator(opt_t opt);
  fptr_operator_t get_operator(opt_t opt);
  void init_operator();

  //
  // 全局变量
  //
  extern int_t gConstZero;
  extern int_t gConstOne;
  extern int_t gConstNegOne;
  extern flt_t gConstE;
  extern flt_t gConstPI;
  extern flt_t gConstHalfPI;
  extern flt_t gConstDoublePI;
  extern flt_t gConstInf;
  extern flt_t gConstNegInf;
  extern symbol_t gConstUDF;
  extern std::vector<std::string> gSymOpts;
  extern std::vector<std::string> gOptSets;

  //////////////////////////////
  // 调试函数
  //////////////////////////////

  // typedef symbol_t (*fptr_operator_frame_t)(const symbol_t &, const symbol_t &);
  // symbol_t operator_frame(const symbol_t &x, const symbol_t &y, fptr_operator_frame_t fopt);

  std::string print_string(const symbol_t &s);
  std::string print_string(const list_t &l);
  std::string print_string(const symopt_t &o);
  std::string print_string(const optset_t &s);
  std::string print_string(const optcase_t &s);

} // namespace mysym

#endif // MYSYM_H_