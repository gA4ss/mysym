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
  bool abstract_find(const list_t &l, const symbol_t &s);
  void insert(list_t &l, const symbol_t &s, bool found = false);
  void insert(list_t& dl, const list_t &sl, bool found = false);
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

  void init();
  symbol_t create(opt_t opt, std::string literal = "");

  symbol_t make(opt_t opt, const symbol_t &s, bool nas = false);
  symbol_t make(opt_t opt, const symbol_t &s1, const symbol_t &s2, bool nas = false);

  symbol_t make(opt_t opt, std::string s, bool nas = false);
  symbol_t make(opt_t opt, std::string s1, std::string s2, bool nas = false);

  symbol_t make(opt_t opt, std::string s1, const symbol_t &s2, bool nas = false);
  symbol_t make(opt_t opt, const symbol_t &s1, std::string s2, bool nas = false);

#define create_opt(opt) create(opt)
#define create_none() create(kOptNone)
#define create_sym(literal) create(kOptVariate, (literal))
#define create_int(literal) create(kOptInteger, (literal))
#define create_real(literal) create(kOptReal, (literal))
#define undefined create_none()

#define kind(s) get_opt(s)
#define number_of_operands(s) symbol_size(s)
  symbol_t operand(const symbol_t &s, size_t i);

  bool match(const symbol_t &s1, const symbol_t &s2);
  bool match_in(const symbol_t &s1, const symbol_t &s2);
  bool abstract_match(const symbol_t &s1, const symbol_t &s2);
  bool abstract_match_in(const symbol_t &s1, const symbol_t &s2);

  int cmp_operator_priority(opt_t o1, opt_t o2);
  void merge_same_basic_operator(symbol_t &s);
  void merge(symbol_t &s);
  void automatic_simplify(symbol_t &s);

  list_t complete_sub_expressions(const symbol_t &s, bool found = false);
  list_t variables(const symbol_t &s);
  list_t constants(const symbol_t &s);
  list_t integers(const symbol_t &s);
  list_t reals(const symbol_t &s);

#define is_undefined(s) is_none(kind(s))
  bool is_monomial(const symbol_t &s, const symbol_t &x);
  bool is_polynomial(const symbol_t &s, const symbol_t &x);
  int_t degree(const symbol_t &s, const symbol_t &x);

  typedef symbol_t (*fptr_map_t)(const symbol_t &);
  symbol_t map(fptr_map_t fmap, const symbol_t &s);
  symbol_t map(const symbol_t &u, const symbol_t &s, opt_t o = kOptNone);

  std::string print_string(const symbol_t &s);
  std::string print_string(const list_t &l);

  //
  // 分数运算
  //
  symbol_t numerator(const symbol_t &s);
  symbol_t denominator(const symbol_t &s);
  symbol_t frac_to_product(const symbol_t &s);

  //
  // 运算符号
  //
#define abs(s) make(kOptAbs, s, false)
#define minus(s) make(kOptSub, s, false)
#define add(s1, s2) make(kOptAdd, s1, s2, false)
#define sub(s1, s2) make(kOptSub, s1, s2, false)
#define mul(s1, s2) make(kOptMul, s1, s2, false)
#define div(s1, s2) make(kOptDiv, s1, s2, false)
#define mod(s1, s2) make(kOptMod, s1, s2, false)
#define sqrt(s1, s2) make(kOptSqrt, s1, s2, false)
#define pow(s1, s2) make(kOptPow, s1, s2, false)
#define log(s1, s2) make(kOptLog, s1, s2, false)
#define frac(s1, s2) make(kOptFrac, s1, s2, false)
#define sin(s) make(kOptSin, s, false)
#define cos(s) make(kOptCos, s, false)
#define tan(s) make(kOptTan, s, false)
#define cot(s) make(kOptCot, s, false)
#define sec(s) make(kOptSec, s, false)
#define csc(s) make(kOptCsc, s, false)
#define asin(s) make(kOptArcSin, s, false)
#define acos(s) make(kOptArcCos, s, false)
#define atan(s) make(kOptArcTan, s, false)
#define acot(s) make(kOptArcCot, s, false)
#define asec(s) make(kOptArcSec, s, false)
#define acsc(s) make(kOptArcCsc, s, false)
#define sinh(s) make(kOptSinh, s, false)
#define cosh(s) make(kOptCosh, s, false)
#define tanh(s) make(kOptTanh, s, false)
#define coth(s) make(kOptCoth, s, false)
#define sech(s) make(kOptSech, s, false)
#define csch(s) make(kOptCsch, s, false)
#define asinh(s) make(kOptArcSinh, s, false)
#define acosh(s) make(kOptArcCosh, s, false)
#define atanh(s) make(kOptArcTanh, s, false)
#define acoth(s) make(kOptArcCoth, s, false)
#define asech(s) make(kOptArcSech, s, false)
#define acsch(s) make(kOptArcCsch, s, false)

  //
  // 全局变量
  //

} // namespace mysym

#endif // MYSYM_H_