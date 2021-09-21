#pragma once
#include <array>
#include <iterator>
#include <type_traits>

// definition of sortable set (with: begging, size and end)
template <typename T>
concept is_container = requires(T i) {
  i.begin();
  i.end();
  i.size();
};

// returns type name of elements in container
#define TYPE(T) typename T::value_type

// construct array from template type (helper function)
#define MAKE_ARRAY(T)                                                          \
  std::array<typename T::value_type, sizeof(T) / sizeof(TYPE(T))>

// check if template argument is same length array (is array valid)
template <typename T>
concept is_array = std::is_same_v<T, MAKE_ARRAY(T)>;

// return size of array
template <typename T>
requires is_array<T>
constexpr std::size_t array_size() { return sizeof(T) / sizeof(TYPE(T)); }

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
template <typename T>
requires is_container<T>
void selection(T &list) {
  using typ = typename T::iterator;
  typ start_iter = list.begin();

  while (start_iter != list.end()) {
    typ min_el = min_element(start_iter, list.end());
    swap(*start_iter, *min_el);
    start_iter++;
  }
}

// bubble sort algorithm: O(n^2)
template <typename T>
requires is_container<T>
void bubble(T &list) {
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

// insertion sort algorithm: O(n^2)
template <typename T>
requires is_container<T>
void insertion(T &list) {
  using typ = TYPE(T);

  for (unsigned int i = 0; i < list.size(); i++) {
    typ key = *(list.begin() + i);
    int j = i - 1;

    // shift all elements forward to make space
    while (j >= 0 && list[j] > key) {
      *(list.begin() + j + i) = *(list + j);
      j = j - 1;
    }
    *(list + j + 1) = key;
  }
}

// merge two smaller array (helper function)
void partial_merge(int array[], int const left, int const mid,
                   int const right) {
  auto const subArrayOne = mid - left + 1;
  auto const subArrayTwo = right - mid;

  // Create temp arrays
  auto *leftArray = new int[subArrayOne], *rightArray = new int[subArrayTwo];

  // Copy data to temp arrays leftArray[] and rightArray[]
  for (auto i = 0; i < subArrayOne; i++)
    leftArray[i] = array[left + i];
  for (auto j = 0; j < subArrayTwo; j++)
    rightArray[j] = array[mid + 1 + j];

  auto indexOfSubArrayOne = 0,   // Initial index of first sub-array
      indexOfSubArrayTwo = 0;    // Initial index of second sub-array
  int indexOfMergedArray = left; // Initial index of merged array

  // Merge the temp arrays back into array[left..right]
  while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
    if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
      array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
      indexOfSubArrayOne++;
    } else {
      array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
      indexOfSubArrayTwo++;
    }
    indexOfMergedArray++;
  }
  // Copy the remaining elements of
  // left[], if there are any
  while (indexOfSubArrayOne < subArrayOne) {
    array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
    indexOfSubArrayOne++;
    indexOfMergedArray++;
  }
  // Copy the remaining elements of
  // right[], if there are any
  while (indexOfSubArrayTwo < subArrayTwo) {
    array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
    indexOfSubArrayTwo++;
    indexOfMergedArray++;
  }

  delete[] leftArray;
  delete[] rightArray;
}

// merge recursive depth first search with partial merge
void merge_wrapper(int array[], int const begin, int const end) {
  if (begin >= end)
    return; // Returns recursively

  auto mid = begin + (end - begin) / 2;
  merge_wrapper(array, begin, mid);
  merge_wrapper(array, mid + 1, end);
  partial_merge(array, begin, mid, end);
}

// merge sort O(n*log(n))
template <typename T>
requires is_container<T>
void merge(T &list) { merge_wrapper(list.begin(), 0, list.size()); }
