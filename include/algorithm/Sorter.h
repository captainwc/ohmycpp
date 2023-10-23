//
// Created by j50036120 on 2023/9/28.
//

#ifndef LEETCODE_CPP_SORTER_H
#define LEETCODE_CPP_SORTER_H

#include "list/List.h"
#include <random>
#include <vector>

namespace mine {
template <typename T> void swap(T &a, T &b) { std::swap(a, b); }

template <typename T> void swap(ListNode<T> &a, ListNode<T> &b) {
  auto tmp = a;
  a = b;
  b = tmp;
}
} // namespace mine

// C should be a container, and override the operator[] >= <= =
template <typename C> int partition(C &elems, int lo, int hi) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(lo, hi);
  int idx = dis(gen);

  mine::swap(elems[lo], elems[idx]);
  auto pivot = elems[lo];
  while (lo < hi) {
    while (lo < hi && elems[hi] >= pivot) {
      hi--;
    }
    elems[lo] = elems[hi];
    while (lo < hi && elems[lo] <= pivot) {
      lo++;
    }
    elems[hi] = elems[lo];
  }
  elems[lo] = pivot;
  return lo;
}

template <typename C> void quickSortHelper(C &elems, int lo, int hi) {
  if (lo < hi) {
    int pos = partition(elems, lo, hi);
    quickSortHelper(elems, lo, pos - 1);
    quickSortHelper(elems, pos + 1, hi);
  }
}

template <typename C> void quickSort(C &elems, int size) {
  quickSortHelper(elems, 0, size - 1);
}

#endif // LEETCODE_CPP_SORTER_H
