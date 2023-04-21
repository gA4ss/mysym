#include <mysym/set.h>

namespace mysym
{
  set_t create_set(const set_elements_t& es)
  {
    set_t s;
    for (auto it = es.begin(); it != es.end(); it++)
      s.insert(*it);
    return s;
  }

  set_t import_set(const set_t& d, const set_t& s)
  {
    set_t r = d;
    for (auto it = s.begin(); it != s.end(); it++)
      r.insert(*it);
    return r;
  }

  bool in_set(const set_t& s, set_element_t e)
  {
    return s.find(e) != s.end();
  }

  set_elements_t in_set(const set_t& s, const set_elements_t& es)
  {
    set_elements_t r;
    for (auto it = es.begin(); it != es.end(); it++)
    {
      if (s.find(*it) != s.end())
        r.push_back(*it);
    }
    return r;
  }

  set_elements_t expand_set(const set_t& s)
  {
    set_elements_t r;
    for (auto it = s.begin(); it != s.end(); it++)
    {
      r.push_back(*it);
    }
    return r;
  }

  set_t intersection_set(const set_t& s1, const set_t& s2)
  {
    set_t r;
    for (auto it = s2.begin(); it != s2.end(); it++)
    {
      if (s1.find(*it) != s1.end())
        r.insert(*it);
    }
    return r;
  }

  set_t union_set(const set_t& s1, const set_t& s2)
  {
    set_t r = s1;
    r.insert(s2.begin(), s2.end());
    return r;
  }

  set_relation_t relation_set(const set_t& s1, const set_t& s2)
  {
    set_t r = intersection_set(s1, s2);

    // 相互不相交
    if (r.empty())
      return kSetNoneIntersect;

    // 两个集合相等
    size_t n = r.size();
    if ((n == s1.size()) && (n == s2.size()))
      return kSet1Equ2;

    // 测试是否包含
    if ((s1.size() > s2.size()) && (n == s2.size()))
      return kSet1Include2;
    else if ((s1.size() < s2.size()) && (n == s1.size()))
      return kSet2Include1;
    
    return kSetIntersect;
  }
} // namespace mysym