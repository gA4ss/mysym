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

  bool as_symopt(std::string name)
  {
    if (__optsets.find(name) == __optsets.end())
      return false;
    auto it = __optsets[name].items.elements.begin();
    int priority = it->second.priority;
    for (; it != __optsets[name].items.elements.end(); it++)
    {
      if (priority != it->second.priority)
        return false;
    }
    return true;
  }

  int optset_priority(std::string name)
  {
    if (__optsets.find(name) == __optsets.end())
      return -1;
    return __optsets[name].average_priority;
  }

  double auto_priority(std::string name)
  {
    if (is_symopt(name))
      return opt_priority(name);
    return optset_priority(name);
  }

  bool find_optset(std::string name, optset_t &out)
  {
    if (__optsets.find(name) == __optsets.end())
      return false;
    out = __optsets[name];
    return true;
  }

  static void __fill_priority(optset_t &os)
  {
    int priority = 0, c = 0;
    double total = 0.0;
    os.max_priority = 0; os.min_priority = 100;
    for (auto it = os.items.elements.begin(); it != os.items.elements.end(); it++)
    {
      priority = it->second.priority;
      os.priority_array.insert(priority);
      if (os.min_priority > priority)
        os.min_priority = priority;
      if (os.max_priority < priority)
        os.max_priority = priority;
      total += priority;
      c++;
    }
    os.average_priority = total / c;
  }

  optset_t create_optset(std::string setname, std::vector<std::string> names)
  {
    optset_t os, found;
    os.name = setname;
    os.id = make_optid(setname);
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

    // 填充优先级
    __fill_priority(os);

    // 更新集合
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
    opts_t include_symopts = expand_optset("all");
    for (auto name : names)
    {
      if (is_symopt(name))
      {
        auto found = std::find(include_symopts.begin(), include_symopts.end(), name);
        if (found != std::end(include_symopts))
        {
          include_symopts.erase(found);
        }
      }
      else if (is_optset(name))
      {
        opts_t opts = expand_optset(name);
        for (auto opt : opts)
        {
          auto found = std::find(include_symopts.begin(), include_symopts.end(), opt);
          if (found != std::end(include_symopts))
          {
            include_symopts.erase(found);
          }
        }
      }/* end else if */
    }
    return create_optset(setname, include_symopts);
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

  typedef symopt_set_t (*fptr_do_optset_t)(const symopt_set_t& s1, const symopt_set_t& s2);
  static opts_t __do_optset(std::string s1, std::string s2, fptr_do_optset_t func)
  {
    optset_t os1,os2;
    if ((find_optset(s1, os1) == false) || (find_optset(s2, os2) == false))
      return {};
    symopt_set_t is = func(os1.items, os2.items);
    if (is.size() == 0)
      return {};

    // 将symopt_set_t类型专程opts_t类型
    opts_t r;
    for (auto it = is.elements.begin(); it != is.elements.end(); it++)
    {
      r.push_back(it->first);
    }
    return r;
  }

  opts_t intersection_optset(std::string s1, std::string s2)
  {
    return __do_optset(s1, s2, intersection_set<symopt_t>);
  }

  opts_t union_optset(std::string s1, std::string s2)
  {
    return __do_optset(s1, s2, union_set<symopt_t>);
  }

  opts_t complementary_optset(std::string s, std::string i)
  {
    return __do_optset(s, i, complementary_set<symopt_t>);
  }

  opts_pair_t difference_optset(std::string s1, std::string s2)
  {
    optset_t os1,os2;
    if ((find_optset(s1, os1) == false) || (find_optset(s2, os2) == false))
      return {};
    symopt_set_pair_t ds = difference_set<symopt_t>(os1.items, os2.items);

    opts_pair_t r;
    for (auto it = ds.first.elements.begin(); it != ds.first.elements.end(); it++)
    {
      r.first.push_back(it->first);
    }
    for (auto it = ds.second.elements.begin(); it != ds.second.elements.end(); it++)
    {
      r.second.push_back(it->first);
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

  optid_t opts_id(std::string name)
  {
    if (__optsets.find(name) == __optsets.end())
      return 0;
    return __optsets[name].id;
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