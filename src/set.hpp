#ifndef MYSYM_SET_H_
#define MYSYM_SET_H_

#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

namespace mysym
{
  typedef enum {
    kSetNoneIntersect = 0,
    kSet1Equ2 = 1,
    kSet1Include2 = 2,
    kSet2Include1 = 4,
    kSetIntersect = 7,
  } set_relation_t;

  typedef std::string set_element_t;
  typedef std::vector<set_element_t> set_elements_t;

  template <typename T>
  class set_t
  {
  public:
    set_t(){}
    virtual ~set_t(){}
    size_t size()
    {
      return elements.size();
    }
    size_t size() const
    {
      return elements.size();
    }

  public:
    std::unordered_map<set_element_t, T> elements;
  };

  template <typename T>
  set_t<T> create_set(const set_elements_t& es, const std::vector<T>& vs)
  {
    // mysym_assert(es.size() == vs.size(), 
    //              "size of elements = %lu, sizeof of values = %lu",
    //              es.size(), vs.size());
    set_t<T> r;
    for (size_t i = 0; i < es.size(); i++)
    {
      r.elements[es[i]] = vs[i];
    }
    return r;
  }

  template <typename T>
  set_t<T> import_set(const set_t<T>& d, const set_t<T>& s)
  {
    set_t<T> r = d;
    for (auto it = s.elements.begin(); it != s.elements.end(); it++)
    {
      if (!in_set(d, it->first))
        r.elements[it->first] = it->second;
    }
    return r;
  }

  template <typename T>
  bool in_set(const set_t<T>& s, set_element_t e)
  {
    return s.elements.find(e) != s.elements.end();
  }

  template <typename T>
  set_elements_t in_set(const set_t<T>& s, const set_elements_t& es)
  {
    set_elements_t r;
    for (auto it = es.begin(); it != es.end(); it++)
    {
      if (s.elements.find(*it) != s.elements.end())
        r.push_back(*it);
    }
    return r;
  }

  template <typename T>
  std::vector<std::pair<set_element_t, T>> expand_set(const set_t<T>& s)
  {
    std::vector<std::pair<set_element_t, T>> r;
    for (auto it = s.elements.begin(); it != s.elements.end(); it++)
    {
      r.push_back({it->first, it->second});
    }
    return r;
  }

  template <typename T>
  set_t<T> intersection_set(const set_t<T>& s1, const set_t<T>& s2)
  {
    set_t<T> r;
    for (auto it = s2.elements.begin(); it != s2.elements.end(); it++)
    {
      if (s1.elements.find(it->first) != s1.elements.end())
        r.elements[it->first] = it->second;
    }
    return r;
  }

  template <typename T>
  set_t<T> union_set(const set_t<T>& s1, const set_t<T>& s2)
  {
    set_t<T> r = s1;
    for (auto it = s2.elements.begin(); it != s2.elements.end(); it++)
      r.elements[it->first] = it->second;
    return r;
  }

  template <typename T>
  set_t<T> complementary_set(const set_t<T>& s, const set_t<T>& i)
  {
    set_t<T> c;
    for (auto it = s.elements.begin(); it != s.elements.end(); it++)
    {
      if (!in_set(i, it->first))
      {
        c.elements[it->first] = it->second;
      }
    }
    return c;
  }

  template <typename T>
  std::pair<set_t<T>, set_t<T>> difference_set(const set_t<T>& s1, const set_t<T>& s2)
  {
    std::pair<set_t<T>, set_t<T>> ds;
    set_t<T> i = intersection_set(s1, s2);

    if (i.size() == 0)
    {
      ds.first = s1;
      ds.second = s2;
    }
    else
    {
      ds.first = complementary_set(s1, i);
      ds.second = complementary_set(s2, i);
    }

    return ds;
  }

  template <typename T>
  set_relation_t relation_set(const set_t<T>& s1, const set_t<T>& s2)
  {
    set_t<T> r = intersection_set(s1, s2);

    // 相互不相交
    if (r.elements.empty())
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

} //namespace mysym

#endif // MYSYM_SET_HPP_