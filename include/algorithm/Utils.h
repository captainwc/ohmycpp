//
// Created by j50036120 on 2023/9/28.
//

#ifndef LEETCODE_CPP_UTILS_H
#define LEETCODE_CPP_UTILS_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <locale.h>
#include <unistd.h>

#define OUT(x) std::cout << (x) << std::endl;

template <typename T> std::string vector2string(const std::vector<T>& vc) {
    std::string ret = "[";
    for (auto x : vc) {
        ret.append(x);
        ret.append(", ");
    }
    return ret.append("]");
}

template <typename T> void printVecvor(const std::vector<T>& vc) {
    for (auto x : vc) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// print progress bar
inline void progressBar(int p, int total, const char* msg = "", int width = 49) {
    printf("\033[s\033[H\033[0m");
    int x = p;
    int y = total;
    double pre = static_cast<double>(p);
    if (total > width) {
        pre   = pre / (static_cast<double>(total) / width);
        total = width;
    }

    setlocale(LC_ALL, "");
    if (pre > total || std::abs(total - pre) < 1e-6) {
        printf("\033[?25I\033[32m【%s \u25c9 FINSH】\033[0m", msg);
        printf("\033[u\033[0m");
        printf("\r");
        printf("\033[?25I\033[32m【%s \u25c9 FINSH】\033[0m", msg);
        fflush(stdout);
        return;
    }

    printf("\r");
    printf("\033[?25I\033[31m【%s %6.2lf%%】\033[0m", msg, pre / total * 100.0);
    for (int i = 0; i < total; i++) {
        printf("\u2593");
    }
    // printf("[%4d/%4d]", x, y);
    fflush(stdout);

    printf("\r");
    printf("\033[?25I\033[31m【%s %6.2lf%%】\033[0m", msg, pre / total * 100.0);
    for (int i = 0; i < pre; i++) {
        printf("\u2588");
    }
    fflush(stdout);
    printf("\033[u\033[0m");
}

#endif // LEETCODE_CPP_UTILS_H
