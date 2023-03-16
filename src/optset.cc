#include <mysym/mysym.h>

namespace mysym
{
  //
  // 记录了所有的集合
  //
  static std::map<std::string, optset_t> __optsets;

  optset_t create_set(std::string setname, std::string optnames)
  {
    optset_t os;
    return os;
  }

  optset_t create_set(std::string setname, optnames_t optnames)
  {
    optset_t os;
    return os;
  }

  optset_t create_set_include_sets(std::string setname, std::string setnames)
  {
    optset_t os;
    return os;
  }

  optset_t create_set_exclude_sets(std::string setname, std::string setnames)
  {
    optset_t os;
    return os;
  }

  bool in_set(std::string setname, std::string optname)
  {
    return false;
  }

  optnames_t in_set(std::string setname, optnames_t optnames)
  {
    optnames_t ons;
    return ons;
  }

  std::string symopts()
  {
    return "";
  }

#define define_opt_set(sn, ons) create_set(sn, ons)
#define define_opt_set_include_sets(sn, oss) create_set_include_sets(sn, oss)
#define define_opt_set_exclude_sets(sn, oss) create_set_exclude_sets(sn, oss)

  void init_symset()
  {
#include "optset.def"
  }

} // namespace mysym