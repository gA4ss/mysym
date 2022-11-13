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

#include <mysym/symopt.h>
#include <mysym/compile.h>
#include <mysym/exception.h>
#include <mysym/debug.h>

namespace mysym
{

  typedef struct __symbol_t
  {
    opt_t opt; // 操作符
    std::string name;
    std::vector<std::shared_ptr<__symbol_t>> next;

    __symbol_t();
    void link(std::shared_ptr<__symbol_t> s);
    bool earse(std::shared_ptr<__symbol_t> s);
  } symbol_t;

  typedef std::shared_ptr<symbol_t> symbol_ptr_t;
  typedef std::vector<symbol_ptr_t> symbol_link_t;
  typedef symbol_link_t::iterator symbol_link_iter_t;
  typedef std::map<opt_t, int> symbol_names_t;
  typedef std::vector<std::string> symbol_strings_t;
  typedef struct __library_t
  {
    symbol_names_t names;
    symbol_strings_t strings;

    __library_t();
    std::string find(const symbol_ptr_t &ptr);
  } library_t;
  typedef std::shared_ptr<library_t> library_ptr_t;

  //
  // 符号名称表
  //
  extern library_ptr_t __plibrary;
#define plibrary() __plibrary
  library_ptr_t init_library();

#define get_name(p) plibrary()->find(p)
#define ret_name(o) plibrary()->strings[plibrary()->names[o]]
#define make_symbol_ptr() std::make_shared<symbol_t>()
#define get_opt(s) (s)->opt
#define link_size(s) (s->next.size())
#define is_single(s) (!link_size(s))
#define is_unary_operation(s) (is_opt(s->opt) && (link_size(s) == 1))

  void init();
  symbol_ptr_t create(opt_t opt, std::string name = "");

  symbol_ptr_t make(opt_t opt, symbol_ptr_t s);
  symbol_ptr_t make(opt_t opt, symbol_ptr_t s1, symbol_ptr_t s2);

  symbol_ptr_t make_(opt_t opt, std::string s);
  symbol_ptr_t make_(opt_t opt, std::string s1, std::string s2);

  symbol_ptr_t func(std::string fn, std::vector<symbol_ptr_t> args);
  symbol_ptr_t func_(std::string fn, std::vector<std::string> args);

  #include "__create.h"

  void merge_same_operator(symbol_ptr_t s);
  std::string print_string(symbol_ptr_t s);

} // namespace mysym


#endif // MYSYM_H_