#ifndef MYSYM_SET_H_
#define MYSYM_SET_H_

#include <string>
#include <unordered_set>
#include <vector>

namespace mysym
{
  typedef enum {
    kSetNoneIntersect = 0,
    kSetIntersect = 1,
    kSet1Include2 = 2,
    kSet2Include1 = 3,
    kSet1Equ2 = 4
  } set_relation_t;

  typedef std::string set_element_t;
  typedef std::vector<set_element_t> set_elements_t;
  typedef std::unordered_set<set_element_t> set_t;

  set_t create_set(const set_elements_t& es);
  set_t import_set(const set_t& d, const set_t& s);
  bool in_set(const set_t& s, set_element_t e);
  set_elements_t in_set(const set_t& s, const set_elements_t& es);
  set_elements_t expand_set(const set_t& s);
  set_t intersection_set(const set_t& s1, const set_t& s2);
  set_t union_set(const set_t& s1, const set_t& s2);
  set_relation_t relation_set(const set_t& s1, const set_t& s2);
} //namespace mysym

#endif // MYSYM_SET_HPP_