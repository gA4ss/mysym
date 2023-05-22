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

#include <mysym/symopt.h>
#include <mysym/compile.h>
#include <mysym/exception.h>
#include <mysym/debug.h>

namespace mysym
{

  // typedef mympz::bignum_t symnum_t;
  typedef mympz::bignum_t integer_t;
  typedef mympf::float_t float_t;

  typedef struct __symbol_t
  {
    opt_t opt; // 操作符
    std::string literal;
    std::vector<struct __symbol_t> items;

    __symbol_t();

  } symbol_t;

  typedef std::shared_ptr<symbol_t> symbol_ptr_t;
  typedef std::vector<symbol_t> symbol_items_t;
  typedef std::map<opt_t, std::string> operator_names_t;

  void append(symbol_t &y, const symbol_t &x);
  void append(symbol_t& y, const symbol_items_t &x);

  //
  // 使用符号严格限定的几个类型
  //
  typedef symbol_t var_t;
  typedef symbol_t num_t;
  typedef symbol_t int_t;
  typedef symbol_t flt_t;

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
#define create_monomial(items) create(kOptMul, items)
#define create_polynomial(items) create(kOptAdd, items)
#define undefined create_none()

  void copy(const symbol_t &s, symbol_t &d);

#define kind(s) get_opt(s)
#define number_of_operands(s) symbol_size(s)
  symbol_t operand(const symbol_t &s, size_t i);
  symbol_t base(const symbol_t &s);
  symbol_t exponent(const symbol_t &s);
  symbol_t term(const symbol_t &s);
  symbol_t constant(const symbol_t &s);
#define antilog(s) exponent(s)
  symbol_t term(const symbol_t &s);
  symbol_t constant(const symbol_t &s);

  bool match(const symbol_t &s1, const symbol_t &s2);
  bool match_in(const symbol_t &s1, const symbol_t &s2);

  int compare(const symbol_t &s1, const symbol_t &s2);
  void sort(symbol_t &s, bool reverse = false);
  void automatic_simplify(symbol_t &s);

  list_t complete_sub_expressions(const symbol_t &s, bool found = false);
  bool free_of(const symbol_t &s, const symbol_t &u);
  bool free_of(const symbol_t &s, const list_t &xs);
  list_t variables(const symbol_t &s);
  list_t constants(const symbol_t &s);
  list_t integers(const symbol_t &s);
  list_t reals(const symbol_t &s);

#define is_undefined(s) is_none(kind(s))
  bool is_monomial(const symbol_t &s, const symbol_t &x);
  bool is_monomial(const symbol_t &s, const list_t &xs);
  bool is_polynomial(const symbol_t &s, const symbol_t &x);
  bool is_polynomial(const symbol_t &s, const list_t &xs);
  int_t degree(const symbol_t &s, const symbol_t &x);
  int_t degree(const symbol_t &s, const list_t &xs);
  int_t coefficient(const symbol_t &s, const symbol_t &x, const int_t &d);
  int_t leading_coefficient(const symbol_t &s, const symbol_t &x);

  typedef symbol_t (*fptr_map_t)(const symbol_t &);
  symbol_t map(fptr_map_t fmap, const symbol_t &s);
  symbol_t map(const symbol_t &u, const symbol_t &s, opt_t o = kOptNone, bool ex = false);

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
  bool cmp_optsign(const optsign_t& i, const optsign_t& j);
  optcase_t generate_optcase(std::string ops);

  // 条件-执行表
  typedef bool (*fptr_condition_t)(opt_t, const symbol_t &, const symbol_t &);
  typedef symbol_t (*fptr_entry_t)(const symbol_t &);
  typedef symbol_t (*fptr_execute_t)(const symbol_t &, const symbol_t &);
  // typedef struct __cmp_rule_table_t
  // {
  //   bool operator()(const optsign_t &i, const optsign_t &j) const
  //   {
  //     return cmp_optsign(i, j);
  //   }
  // } cmp_rule_table_t;
  // typedef std::map<optsign_t, fptr_execute_t, cmp_rule_table_t> rule_table_t;
  typedef std::pair<optsign_t, fptr_execute_t> rule_case_t;
  typedef std::vector<rule_case_t> rule_table_t;
  typedef std::unordered_map<optsign_t, size_t> rule_table_index_t;
  typedef std::unordered_map<opt_t, rule_table_index_t> rule_case_query_t;
  // 条件执行项目
  typedef std::unordered_map<opt_t, fptr_entry_t> rule_entry_t;
  typedef std::unordered_map<opt_t, rule_table_t> rule_object_t;

  typedef struct __rule_library_t
  {
    rule_entry_t entries;
    rule_object_t cases;
    rule_case_query_t casetbl;
  } rule_library_t;
  rule_library_t &rule_library();

  void register_atom_rule();
  void register_cmp_rule();
  void register_add_rule();
  void register_mul_rule();
  void register_func_rule();
  void init_rule();
  
  bool find_entry(opt_t opt);
  bool find_case(opt_t opt, optsign_t ops, fptr_execute_t *fptr = nullptr);
  void append_entry(opt_t opt, fptr_entry_t fentry);
  void append_case(opt_t opt, optsign_t sign, fptr_execute_t fexecute);
  void register_case(opt_t opt, optsign_t sign, fptr_execute_t fexecute);
  void sort_case(opt_t opt);
  symbol_t execute_entry(const symbol_t &x);
  symbol_t execute_cases(opt_t opt, const symbol_t &x, const symbol_t &y);
  void apply_rule(symbol_t &x);

  symbol_t default_entry(const symbol_t &x);
  symbol_t default_execute(const symbol_t &x, const symbol_t &y);

  void default_cases(opt_t opt, std::string ops);
  void append_optcase_string(std::string &ops, const std::string op);
  void append_optcase_string(std::string &ops, const std::vector<std::string> opl);

  //
  // 基础运算律
  //
  void apply_associative_law(symbol_t &x);
  void apply_commutative_law(symbol_t &x);
  void apply_distributive_law(symbol_t &x);
  void combine_like_terms(symbol_t &x);
  void format(symbol_t &x);
  void play(symbol_t &x);
  void apply_basic_rule(symbol_t &x);

  //
  // 运算符号
  //
#define c_add(s1, s2) make(kOptAdd, s1, s2, false)
#define c_mul(s1, s2) make(kOptMul, s1, s2, false)
#define c_equ(s1, s2) make(kOptEqu, s1, s2, false)
#define c_neq(s1, s2) make(kOptNotEqu, s1, s2, false)
#define c_lt(s1, s2) make(kOptLT, s1, s2, false)
#define c_le(s1, s2) make(kOptLE, s1, s2, false)
#define c_gt(s1, s2) make(kOptGT, s1, s2, false)
#define c_ge(s1, s2) make(kOptGE, s1, s2, false)
#define c_cmp(s1, s2) make(kOptCmp, s1, s2, false)
#define c_pow(s1, s2) make(kOptPow, s1, s2, false)
#define c_log(s1, s2) make(kOptLog, s1, s2, false)
#define c_fact(s1, s2) make(kOptFact, s1, s2, false)
#define c_abs(s) make(kOptAbs, s, false)
#define c_mod(s1, s2) make(kOptMod, s1, s2, false)
#define c_sin(s) make(kOptSin, s, false)
#define c_cos(s) make(kOptCos, s, false)
#define c_tan(s) make(kOptTan, s, false)
#define c_cot(s) make(kOptCot, s, false)
#define c_sec(s) make(kOptSec, s, false)
#define c_csc(s) make(kOptCsc, s, false)
#define c_asin(s) make(kOptArcSin, s, false)
#define c_acos(s) make(kOptArcCos, s, false)
#define c_atan(s) make(kOptArcTan, s, false)
#define c_acot(s) make(kOptArcCot, s, false)
#define c_asec(s) make(kOptArcSec, s, false)
#define c_acsc(s) make(kOptArcCsc, s, false)
#define c_sinh(s) make(kOptSinh, s, false)
#define c_cosh(s) make(kOptCosh, s, false)
#define c_tanh(s) make(kOptTanh, s, false)
#define c_coth(s) make(kOptCoth, s, false)
#define c_sech(s) make(kOptSech, s, false)
#define c_csch(s) make(kOptCsch, s, false)
#define c_asinh(s) make(kOptArcSinh, s, false)
#define c_acosh(s) make(kOptArcCosh, s, false)
#define c_atanh(s) make(kOptArcTanh, s, false)
#define c_acoth(s) make(kOptArcCoth, s, false)
#define c_asech(s) make(kOptArcSech, s, false)
#define c_acsch(s) make(kOptArcCsch, s, false)
#define c_frac(s1, s2) make(kOptFrac, s1, s2, false)

  //
  // 扩展运算符
  //
#define c_minus(s) c_mul(create_int("-1"), s)
#define c_sub(s1, s2) make(kOptAdd, s1, c_mul(create_int("-1"), s2), false)
#define c_div(s1, s2) make(kOptMul, s1, c_pow(s2, create_int("-1")), false)
#define c_sqrt(s) make(kOptPow, s, create_frac("1", "2"), false)

  //
  // 符号运算符
  //
  symbol_t frac_entry(const symbol_t &x);   // 分数运算的入口需要特殊处理
  symbol_t default_func_handler(opt_t opt, const symbol_t &x);
  symbol_t default_func_handler(opt_t opt, const symbol_t &x, const symbol_t &y);
  symbol_t add(const symbol_t &x, const symbol_t &y);
  symbol_t mul(const symbol_t &x, const symbol_t &y);
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
  // 全局变量
  //
  extern int_t gConstZero;
  extern int_t gConstOne;
  extern int_t gConstNegOne;
  extern flt_t gConstE;
  extern flt_t gConstPI;
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
  std::string print_string(const optset_t& s);
  std::string print_string(const optcase_t& s);

} // namespace mysym

#endif // MYSYM_H_