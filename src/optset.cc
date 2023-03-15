#include <mysym/mysym.h>

namespace mysym
{
  //
  // 记录了所有的集合
  //
  static std::map<std::string, optset_t> __optsets;

  optset_t create(std::string setname, std::string optnames)
  {
    optset_t os;
    return os;
  }

  optset_t create(std::string setname, optnames_t optnames)
  {
    optset_t os;
    return os;
  }

  optset_t create_from_set(std::string setname, std::vector<std::string> setnames)
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
} // namespace mysym