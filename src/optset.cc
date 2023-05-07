#include <mysym/mysym.h>
#include <mysym/set.hpp>
#include "__misc.h"

namespace mysym
{
  //
  // 记录了所有的集合
  //
  static std::map<std::string, optset_t> __optsets;

  size_t size(optset_t os)
  {
    return os.items.size();
  }

  size_t size_optset(std::string setname)
  {
    optset_t os;
    if (find_optset(setname, os) == false)
      return -1;
    return os.items.size();
  }

  static inline void __update_optsets(optset_t &ops)
  {
    __optsets[ops.name] = ops;
  }

  bool is_optset(std::string name)
  {
    return (__optsets.find(name) != __optsets.end());
  }

  bool find_optset(std::string name, optset_t &out)
  {
    if (__optsets.find(name) == __optsets.end())
      return false;
    out = __optsets[name];
    return true;
  }

  optset_t create_optset(std::string setname, std::vector<std::string> names)
  {
    optset_t os, found;
    os.name = setname;
    symopt_t sopt;
    for (auto name : names)
    {
      if (find_symopt(name, sopt))
      {
        os.items.elements[name] = sopt;
      }
      else if (find_optset(name, found))
      {
        opts_t opts = expand_optset(found);
        for (auto it = opts.begin(); it != opts.end(); it++)
        {
          symopt_t sopt;
          if (find_symopt(*it, sopt))
            os.items.elements[*it] = sopt;
        }
      }/* else if */
    }
    __update_optsets(os);
    return os;
  }

  optset_t create_optset(std::string setname, std::string names)
  {
    std::vector<std::string> strs = split_string(names);
    return create_optset(setname, strs);
  }

  optset_t create_optset_exclude(std::string setname, std::string setnames)
  {
    std::vector<std::string> names = split_string(setnames);
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
    return create_optset(setname, include_sets);
  }

  bool in_optset(std::string setname, std::string optname)
  {
    optset_t ops;
    if (find_optset(setname, ops))
    {
      return in_set<symopt_t>(ops.items, optname);
    }
    return false;
  }

  opts_t in_optset(std::string setname, opts_t optnames)
  {
    opts_t ons;
    optset_t ops;
    if (find_optset(setname, ops))
    {
      for (auto opt : optnames)
      {
        if (in_set<symopt_t>(ops.items, opt))
          ons.push_back(opt);
      }
    }
    return ons;
  }

  opts_t expand_optset(const optset_t& s)
  {
    opts_t opts;
    for (auto it = s.items.elements.begin(); it != s.items.elements.end(); it++)
    {
      opts.push_back(it->first);
    }
    return opts;
  }

  opts_t expand_optset(std::string setname)
  {
    optset_t s;
    if (find_optset(setname, s) == false)
      return {};
    return expand_optset(s);
  }

  opts_t intersection_optset(std::string s1, std::string s2)
  {
    optset_t os1,os2;
    if ((find_optset(s1, os1) == false) || (find_optset(s2, os2) == false))
      return {};
    symopt_set_t is = intersection_set<symopt_t>(os1.items, os2.items);
    if (is.size() == 0)
      return {};

    opts_t r;
    for (auto it = is.elements.begin(); it != is.elements.end(); it++)
    {
      r.push_back(it->first);
    }
    return r;
  }

  opts_t union_optset(std::string s1, std::string s2)
  {
    optset_t os1,os2;
    if ((find_optset(s1, os1) == false) || (find_optset(s2, os2) == false))
      return {};
    symopt_set_t is = union_set<symopt_t>(os1.items, os2.items);
    if (is.size() == 0)
      return {};

    opts_t r;
    for (auto it = is.elements.begin(); it != is.elements.end(); it++)
    {
      r.push_back(it->first);
    }
    return r;
  }

  set_relation_t relation_optset(std::string s1, std::string s2)
  {
    optset_t os1,os2;
    if ((find_optset(s1, os1) == false) || (find_optset(s2, os2) == false))
      return {};
    return relation_set<symopt_t>(os1.items, os2.items);
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

#define define_optset(sn, ons) create_optset(sn, ons)
#define define_optset_exclude(sn, oss) create_optset_exclude(sn, oss)

  void init_symset()
  {
#include "optset.def"
  }

} // namespace mysym