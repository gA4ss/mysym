#include <mysym/mysym.h>

namespace mysym
{

  size_t size(const list_t& l)
  {
    return l.size();
  }

  bool find(const list_t& l, const symbol_t &s)
  {
    for (auto it = l.begin(); it != l.end(); it++)
    {
      if (match(s, *it))
        return true;
    }
    return false;
  }

  bool abstract_find(const list_t& l, const symbol_t &s)
  {
    for (auto it = l.begin(); it != l.end(); it++)
    {
      if (abstract_match(s, *it))
        return true;
    }
    return false;
  }

  void insert(list_t& l, const symbol_t &s, bool found)
  {
    if (!found)
    {
      l.push_back(s);
    }
    else
    {
      if (!find(l, s))
        l.push_back(s);
    }
  }

  void insert(list_t& dl, const list_t &sl, bool found)
  {
    for (auto it = dl.begin(); it != dl.end(); it++)
    {
      
    }
  }

  void clear(list_t& l)
  {
    l.clear();
  }

} // namespace mysym