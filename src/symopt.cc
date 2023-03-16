#include <mysym/mysym.h>

namespace mysym
{
  typedef std::map<std::string, symopt_t> symopts_t;
  static symopts_t __symopts;

#define define_opt(operator, priority, sorted) __symopts[operator] = {operator, priority, sorted}

  void init_symopt(){
#include "symopt.def"
  }

  std::string opt_name(opt_t o)
  {
    if (__symopts.find(o) == __symopts.end())
      return "";
    return __symopts[o].opt;
  }

  int opt_prio(opt_t o)
  {
    if (__symopts.find(o) == __symopts.end())
      return -1;
    return __symopts[o].prio;
  }

  bool opt_sorted(opt_t o)
  {
    if (__symopts.find(o) == __symopts.end())
      return true;
    return __symopts[o].sorted;
  }

  int cmp_operator_priority(opt_t o1, opt_t o2)
  {
    if (__symopts[o1].prio < __symopts[o2].prio)
      return -1;
    else if (__symopts[o1].prio > __symopts[o2].prio)
      return 1;
    else
      return 0;
  }
} // namespace mysym