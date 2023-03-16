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

#include <mympz/mympz.h>
#include <mympf/mympf.h>
// #include <mynum/mynum.h>

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

  void append(symbol_t &y, const symbol_t &x);

  typedef std::shared_ptr<symbol_t> symbol_ptr_t;
  typedef std::vector<symbol_t> symbol_items_t;
  typedef std::map<opt_t, std::string> operator_names_t;

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
  typedef struct __library_t
  {
    __library_t();
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
  symbol_t create_symbol(std::string literal);

  symbol_t make(opt_t opt, const symbol_t &s, bool nas = false);
  symbol_t make(opt_t opt, const symbol_t &s1, const symbol_t &s2, bool nas = false);

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

  int cmp(const symbol_t &s1, const symbol_t &s2);
  void sort(symbol_t &s, bool reverse = false);
  void merge(symbol_t &s);
  void automatic_simplify(symbol_t &s, bool reverse = false);

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
  symbol_t map(const symbol_t &u, const symbol_t &s, opt_t o = kOptNone);

  // typedef symbol_t (*fptr_operator_frame_t)(const symbol_t &, const symbol_t &);
  // symbol_t operator_frame(const symbol_t &x, const symbol_t &y, fptr_operator_frame_t fopt);

  std::string print_string(const symbol_t &s);
  std::string print_string(const list_t &l);

  //
  // 分数运算
  //
  symbol_t numerator(const symbol_t &s);
  symbol_t denominator(const symbol_t &s);
  symbol_t frac_to_product(const symbol_t &s);

  //
  // 规则表
  //

  // 条件-执行表
  typedef bool (*fptr_condition_s_t)(const symbol_t &);
  typedef bool (*fptr_condition_d_t)(const symbol_t &, const symbol_t &);
  typedef symbol_t (*fptr_execute_s_t)(const symbol_t &);
  typedef symbol_t (*fptr_execute_d_t)(const symbol_t &, const symbol_t &);
  typedef std::vector<std::pair<fptr_condition_s_t, fptr_execute_s_t>> rule_table_s_t;
  typedef std::vector<std::pair<fptr_condition_d_t, fptr_execute_d_t>> rule_table_d_t;

  // 条件执行项目
  typedef std::map<opt_t, rule_table_s_t> rule_object_s_t;
  typedef std::map<opt_t, rule_table_d_t> rule_object_d_t;

  typedef struct __rule_library_t
  {
    rule_object_s_t rs;
    rule_object_d_t rd;
  } rule_library_t;

  void register_rule(opt_t opt, fptr_condition_s_t fcondition, fptr_execute_s_t fexecute);
  void register_rule(opt_t opt, fptr_condition_d_t fcondition, fptr_execute_d_t fexecute);
  bool find_rule_table_s(opt_t opt, rule_table_s_t &tab);
  bool find_rule_table_d(opt_t opt, rule_table_d_t &tab);
  bool is_empty(const rule_table_s_t &tab);
  bool is_empty(const rule_table_d_t &tab);
  symbol_t apply_rule_table(const rule_table_s_t &r, const symbol_t &x);
  symbol_t apply_rule_table(const rule_table_d_t &r, const symbol_t &x, const symbol_t &y);
  symbol_t apply_rule(const symbol_t &x);
  void init_rule();

  //
  // 运算符号
  //
#define c_add(s1, s2) make(kOptAdd, s1, s2, false)
#define c_mul(s1, s2) make(kOptMul, s1, s2, false)
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
#define c_c_csch(s) make(kOptCsch, s, false)
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
  symbol_t add(const symbol_t &x, const symbol_t &y);

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

} // namespace mysym

#endif // MYSYM_H_