#include <mysym/mysym.h>
#include <regex>

namespace mysym
{
  static std::vector<std::string> __split_string(std::string str)
  {
    std::vector<std::string> res;
    std::regex reg("[, ]+");
    std::sregex_token_iterator pos(str.begin(), str.end(), reg, -1);
    decltype(pos) end; // 自动推导类型
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
  static inline void __update_optsets(optset_t &ops)
  {
    __optsets[ops.name] = ops;
  }

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
    __update_optsets(os);
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
    __update_optsets(os);
    return os;
  }

  static optset_t __create_set_include_sets(std::string setname, std::vector<std::string> setnames)
  {
    optset_t os;
    os.name = setname;

    optset_t ops;
    // 遍历集合名称
    for (auto sname : setnames)
    {
      // 取出集合
      if (find_optset(sname, ops))
      {
        //
        // 如果找到则查看是否有同名的
        //
        for (auto i : ops.items)
        {
          // 仅保存没有的
          if (os.items.find(i.first) == os.items.end())
          {
            os.items[i.first] = i.second;
          }
        }
      }
    }
    __update_optsets(os);
    return os;
  }

  optset_t create_set_include_sets(std::string setname, std::string setnames)
  {
    std::vector<std::string> include_sets = __split_string(setnames);
    return __create_set_include_sets(setname, include_sets);
  }

  optset_t create_set_exclude_sets(std::string setname, std::string setnames)
  {
    std::vector<std::string> names = __split_string(setnames);
    std::vector<std::string> include_sets;
    // 遍历所有集合
    for (auto ops : __optsets)
    {
      // 如果在排除集合中没有找到
      if (std::find(names.begin(), names.end(), ops.first) == names.end())
      {
        include_sets.push_back(ops.first);
      }
    }

    return __create_set_include_sets(setname, include_sets);
  }

  bool in_set(std::string setname, std::string optname)
  {
    optset_t ops;
    if (find_optset(setname, ops))
    {
      if (ops.items.find(optname) != ops.items.end())
        return true;
    }
    return false;
  }

  std::vector<std::string> in_set(std::string setname, std::vector<std::string> optnames)
  {
    std::vector<std::string> ons;
    optset_t ops;
    if (find_optset(setname, ops))
    {
      for (auto opt : optnames)
      {
        if (ops.items.find(opt) != ops.items.end())
          ons.push_back(opt);
      }
    }
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