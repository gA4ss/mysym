#include <mysym/mysym.h>
#include "__misc.h"

namespace mysym
{

  // static bool __default_condition(const symbol_t &x, const symbol_t &y)
  // {
  //   return is_atom(kind(x));
  // }
  // static symbol_t __default_execute(const symbol_t &x, const symbol_t &y)
  // {
  //   return undefined;
  // }

  typedef std::vector<std::pair<std::string, std::string> > optcase_t;
  static optcase_t __generate_optcase(std::string ops)
  {
    optcase_t cases;
    std::vector<std::string> sets = split_string(ops);
    size_t n = sets.size(), j = 0;
    for (size_t i = 0; i < n; i++)
    {
      j = i;
      for (; j < n; j++)
      {
        cases.push_back({sets[i], sets[j]});
      }
    }
    return cases;
  }

  void register_optcase(opt_t opt, std::string ops)
  {
    optcase_t ops = __generate_optcase(ops);
  }
} // namespace mysym