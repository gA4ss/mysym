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
  // 列表
  //
  typedef symbol_items_t list_t;

  size_t size(const list_t &l);
  bool find(const list_t &l, const symbol_t &s);
  bool abstract_find(const list_t &l, const symbol_t &s);
  void insert(list_t &l, const symbol_t &s, bool found=false);
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

  symbol_t make(opt_t opt, const symbol_t &s, bool as = false);
  symbol_t make(opt_t opt, const symbol_t &s1, const symbol_t &s2, bool as = false);

  symbol_t make(opt_t opt, std::string s, bool as = false);
  symbol_t make(opt_t opt, std::string s1, std::string s2, bool as = false);

  symbol_t make(opt_t opt, std::string s1, const symbol_t &s2, bool as = false);
  symbol_t make(opt_t opt, const symbol_t &s1, std::string s2, bool as = false);

#define create_opt(opt) create(opt)
#define create_sym(literal) create(kOptSymbol, (literal))
#define create_int(literal) create(kOptInteger, (literal))
#define create_real(literal) create(kOptReal, (literal))

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

  bool is_monomial(const symbol_t &s);
  list_t variables(const symbol_t &s);
  list_t constants(const symbol_t &s);
  list_t integers(const symbol_t &s);
  list_t reals(const symbol_t &s);

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
#define abs(s) make(kOptAbs, s, true)
#define minus(s) make(kOptSub, s, true)
#define add(s1, s2) make(kOptAdd, s1, s2, true)
#define sub(s1, s2) make(kOptSub, s1, s2, true)
#define mul(s1, s2) make(kOptMul, s1, s2, true)
#define div(s1, s2) make(kOptDiv, s1, s2, true)
#define mod(s1, s2) make(kOptMod, s1, s2, true)
#define sqrt(s1, s2) make(kOptSqrt, s1, s2, true)
#define pow(s1, s2) make(kOptPow, s1, s2, true)
#define log(s1, s2) make(kOptLog, s1, s2, true)
#define frac(s1, s2) make(kOptFrac, s1, s2, true)
#define sin(s) make(kOptSin, s, true)
#define cos(s) make(kOptCos, s, true)
#define tan(s) make(kOptTan, s, true)
#define cot(s) make(kOptCot, s, true)
#define sec(s) make(kOptSec, s, true)
#define csc(s) make(kOptCsc, s, true)
#define asin(s) make(kOptArcSin, s, true)
#define acos(s) make(kOptArcCos, s, true)
#define atan(s) make(kOptArcTan, s, true)
#define acot(s) make(kOptArcCot, s, true)
#define asec(s) make(kOptArcSec, s, true)
#define acsc(s) make(kOptArcCsc, s, true)
#define sinh(s) make(kOptSinh, s, true)
#define cosh(s) make(kOptCosh, s, true)
#define tanh(s) make(kOptTanh, s, true)
#define coth(s) make(kOptCoth, s, true)
#define sech(s) make(kOptSech, s, true)
#define csch(s) make(kOptCsch, s, true)
#define asinh(s) make(kOptArcSinh, s, true)
#define acosh(s) make(kOptArcCosh, s, true)
#define atanh(s) make(kOptArcTanh, s, true)
#define acoth(s) make(kOptArcCoth, s, true)
#define asech(s) make(kOptArcSech, s, true)
#define acsch(s) make(kOptArcCsch, s, true)

} // namespace mysym

#endif // MYSYM_H_