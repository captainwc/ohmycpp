//
// Created by j50036120 on 2023/9/28.
//

#ifndef LEETCODE_CPP_UTILS_H
#define LEETCODE_CPP_UTILS_H

#include <locale.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "list/ListNode.h"

//==-------------------- ANSI -----------------------==//

#define FC_RED "\033[31m%s\033[0m"

//==-------------------- Print ----------------------==//

template <typename T>
std::string vector2String(const std::vector<T>& vc) {
    std::string ret = "[";
    for (auto x : vc) {
        ret.append(x);
        ret.append(",");
    }
    ret.pop_back();
    return ret.append("]");
}

inline std::string linkList2String(ListNode* head) {
    auto pNode = head;
    std::string str = "[";
    while (pNode != nullptr) {
        str.append(std::to_string(pNode->val) + ",");
        pNode = pNode->next;
    }
    str.pop_back();
    str.append("]");
    return str;
}

template <typename T>
void printVector(const std::vector<T>& vc) {
    std::cout << vector2String(vc) << std::endl;
}

inline void printLinkList(ListNode* head) {
    std::cout << linkList2String(head) << std::endl;
}

//==----------------- Progress Bar ------------------==//

inline void progressBar(int p, int total, const char* msg = "", int width = 49) {
    printf("\033[s\033[H\033[0m");
    int x = p;
    int y = total;
    double pre = static_cast<double>(p);
    if (total > width) {
        pre = pre / (static_cast<double>(total) / width);
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

//==----------------- String Op ---------------------==//

inline std::vector<std::string> splitString(std::string str, std::string sep) {
    std::regex re(sep);
    std::sregex_token_iterator p(str.begin(), str.end(), re, -1);
    std::sregex_token_iterator end;
    std::vector<std::string> vec(p, end);
    return vec;
}

//==----------------- LinkList ----------------------==//
inline ListNode* getLinkList(std::string str) {
    auto ret = splitString(str, ",");
    LinkList list;
    for (auto st : ret) {
        list.push_back(std::stoi(st));
    }
    return list.front();
}

#endif  // LEETCODE_CPP_UTILS_H
