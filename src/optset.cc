#include <mysym/mysym.h>
#include <regex>

namespace mysym
{
  static std::vector<std::string> __split_string(std::string str)
  {
    std::vector<std::string> res;
    std::regex reg("[, ]+");
    std::sregex_token_iterator pos(str.begin(), str.end(), reg, -1);
    decltype(pos) end;          // 自动推导类型 
    for (; pos != end; ++pos)
    {
      res.push_back(pos->str());
    }
    return res;
  }

  //
  // 记录了所有的集合
  //
  static std::map<std::string, optset_t> __optsets;

  bool find_optset(std::string name, optset_t &out)
  {
    if (__optsets.find(name) == __optsets.end())
      return false;
    out = __optsets[name];
    return true;
  }

  optset_t create_set(std::string setname, std::string optnames)
  {
    optset_t os;
    std::vector<std::string> names = __split_string(optnames);
    os.name = setname;
    symopt_t sopt;
    for (auto name : names)
    {
      // 跳过找不到的符号名
      if (find_symopt(name, sopt))
        os.items[name] = sopt;
    }
    return os;
  }

  optset_t create_set(std::string setname, std::vector<std::string> optnames)
  {
    optset_t os;
    os.name = setname;
    symopt_t sopt;
    for (auto name : optnames)
    {
      // 跳过找不到的符号名
      if (find_symopt(name, sopt))
        os.items[name] = sopt;
    }
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

  std::vector<std::string> in_set(std::string setname, std::vector<std::string> optnames)
  {
    std::vector<std::string> ons;
    return ons;
  }

  std::string optsets()
  {
    std::string res;
    for (auto it : __optsets)
    {
      res += it.first;
      res += ",";
    }
    // 弹出最后一个","
    if (!res.empty())
      res.pop_back();
    return res;
  }

#define define_opt_set(sn, ons) create_set(sn, ons)
#define define_opt_set_include_sets(sn, oss) create_set_include_sets(sn, oss)
#define define_opt_set_exclude_sets(sn, oss) create_set_exclude_sets(sn, oss)

  void init_symset()
  {
#include "optset.def"
  }

} // namespace mysym