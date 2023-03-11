#include <mysym/mysym.h>

namespace mysym
{
#define define_opt(operator, name, priority, associative) { \
  operator, \
  name, \
  priority, \
  associative \
}

  operator_t __operator[kOptMax] = {
    #include "symopt.def"
  };

  int cmp_operator_priority(opt_t o1, opt_t o2)
  {
    //
    // 比较符号与运算符
    //
    // if (!is_sym(o1) && is_sym(o2))
    //   return -1;

    // if (is_sym(o1) && !is_sym(o2))
    //   return 1;

    // if (is_sym(o1) && is_sym(o2))
    //   return 0;

    //
    // 运算符间的比较
    //
    if (__operator[o1].prio < __operator[o2].prio)
      return -1;
    else if (__operator[o1].prio > __operator[o2].prio)
      return 1;
    else
      return 0;
  }

  bool is_integer(const num_t &x)
  {
    if (kind(x) != kOptFloat)
      return false;
    
    return my::is_integer(x.literal);
  }

  bool is_real(const num_t &x)
  {
    if (is_nature(kind(x)))
      return true;

    if (kind(x) != kOptFloat)
      return false;
    
    return my::is_real(x.literal);
  }
} // namespace mysym