//
// Created by j50036120 on 2023/9/28.
//

#ifndef LEETCODE_CPP_SORTER_H
#define LEETCODE_CPP_SORTER_H

#include <algorithm>
#include <random>
#include <vector>

#include "list/BLNode.h"

template <typename C>
class Sorter {
public:
    static void quickSort(C& elems, int size) {
        std::sort(elems.begin(), elems.end());
    }
};

#endif  // LEETCODE_CPP_SORTER_H
