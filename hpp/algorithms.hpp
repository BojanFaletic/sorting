#pragma once
#include <iterator>

// find minimum element (std::min_element)
template <typename Iter> Iter min_element(Iter start, Iter end) {
  using typ = typename std::iterator_traits<Iter>::value_type;
  typ best_min = *start;

  Iter min_position = start++;
  while (start < end) {
    if (*start < best_min) {
      best_min = *start;
      min_position = start;
    }
    start++;
  }
  return min_position;
}

// swap two numbers (std::swap)
template <typename Iter> void swap(Iter &first, Iter &second) {
  Iter tmp = first;
  first = second;
  second = tmp;
}

// selection sort algorithm: O(n^2)
template <typename T> void selection(T &list) {
  using typ = typename T::iterator;
  typ start_iter = list.begin();

  while (start_iter != list.end()) {
    typ min_el = min_element(start_iter, list.end());
    swap(*start_iter, *min_el);
    start_iter++;
  }
}

// bubble sort algorithm: O(n^2)
template <typename T> void bubble(T &list) {
  using typ = typename T::iterator;

  for (unsigned int i = 0; i < list.size() - 1; i++) {
    for (typ first = list.begin(); first < list.end() - i - 1; first++) {
      typ second = first + 1;
      if (*second < *first) {
        swap(*first, *second);
      }
    }
  }
}