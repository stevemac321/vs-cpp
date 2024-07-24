/*==============================================================================
 Name        : remove_erase.h
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
/// \file remove_erase.h
/// \brief Got this from STL's channel9 presentation on STL.  Used for testing
/// stevemac::vector::erase
///
//===----------------------------------------------------------------------===//
#pragma once
#include <algorithm>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace remove_erase {
namespace details {
// set up traits
struct vectorlike_tag {};
struct listlike_tag {};
struct associative_tag {};

template <typename C> struct container_traits;

template <typename T, typename A> struct container_traits<std::vector<T, A>> {
  typedef vectorlike_tag category;
};

template <typename T, typename A> struct container_traits<std::deque<T, A>> {
  typedef vectorlike_tag category;
};

template <typename T, typename A> struct container_traits<std::list<T, A>> {
  typedef listlike_tag category;
};

template <typename T, typename A>
struct container_traits<std::forward_list<T, A>> {
  typedef listlike_tag category;
};

template <typename T, typename A> struct container_traits<std::set<T, A>> {
  typedef associative_tag category;
};

template <typename T, typename A> struct container_traits<std::multiset<T, A>> {
  typedef associative_tag category;
};

template <typename T, typename A>
struct container_traits<std::unordered_set<T, A>> {
  typedef associative_tag category;
};

template <typename T, typename A> struct container_traits<std::map<T, A>> {
  typedef associative_tag category;
};

template <typename T, typename A> struct container_traits<std::multimap<T, A>> {
  typedef associative_tag category;
};

template <typename T, typename A>
struct container_traits<std::unordered_map<T, A>> {
  typedef associative_tag category;
};

// helpers
template <typename Container, typename X>
void erase_helper(Container &c, const X &x,
                  vectorlike_tag) { // no instance of vectorlike_tag needed
  c.erase(std::remove(c.begin(), c.end(), x), c.end());
}

template <typename Container, typename Pred>
void erase_if_helper(Container &c, Pred p, vectorlike_tag) {
  c.erase(std::remove_if(c.begin(), c.end(), p), c.end());
}

template <typename Container, typename X>
void erase_helper(Container &c, const X &x, listlike_tag) {
  c.remove(x);
}

template <typename Container, typename Pred>
void erase_if_helper(Container &c, Pred p, listlike_tag) {
  c.remove_if(p);
}

template <typename Container, typename X>
void erase_helper(Container &c, const X &x, associative_tag) {
  c.erase(x);
}

template <typename Container, typename Pred>
void erase_if_helper(Container &c, Pred p, associative_tag) {
  for (auto i = c.begin(); i != c.end(); i++) {
    if (p(*i))
      c.erase(i++);
    else
      ++i;
  }
}
} // end details
} // end remove_erase

/*
examples to call:
map<int, string> v = { { 0, "one" }, { 1, "two" }, { 2, "three" }, { 3, "four" }
};

erase_if_helper(v, [](pair<int, string> p) { return (p.first % 2) == 0;},
associative_tag());

for (auto i : v) {
 do something
}
*/

