#include <mysym/mysym.h>
#include "__misc.h"

namespace mysym
{
  static bool __find_symopt(std::string s)
  {
    return std::find(gSymOpts.begin(), gSymOpts.end(), s) != gSymOpts.end();
  }

  static bool __find_optset(std::string s)
  {
    return std::find(gOptSets.begin(), gOptSets.end(), s) != gOptSets.end();
  }

  bool is_optsign(optsign_t sign)
  {
    std::vector<std::string> s = split_string(sign);
    if (s.size() != 2)
      return false;

    return ((__find_symopt(s[0]) || __find_optset(s[0])) &&
            (__find_symopt(s[1]) || __find_optset(s[1])));
  }

  optsign_t make_optsign(opt_t opt1, opt_t opt2)
  {
    return opt1 + "," + opt2;
  }

  optpair_t split_optcase(optsign_t sign)
  {
    std::vector<std::string> s = split_string(sign);
    mysym_assert(s.size() == 2, "size of optcase is not 2, opc = \'%s\'", sign.c_str());
    return {s[0], s[1]};
  }

  optcase_t generate_optcase(std::string ops)
  {
    optcase_t cases;
    std::vector<std::string> sets = split_string(ops);
    size_t n = sets.size(), j = 0;
    for (size_t i = 0; i < n; i++)
    {
      j = i;
      for (; j < n; j++)
      {
        cases.push_back(make_optsign(sets[i], sets[j]));
        if (sets[i] != sets[j])
        {
          cases.push_back(make_optsign(sets[j], sets[i]));
        }
      }/* end for */
    }
    return cases;
  }
} // namespace mysym