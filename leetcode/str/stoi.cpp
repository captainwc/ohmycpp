/**
 * BRIEF: 解析字符串为整数
 *
 * LINK: https://leetcode.cn/problems/string-to-integer-atoi/
 *
 * IDEA: 自动机 DFA
 *
 * Create by shuaikai 2024/02/22 20:07:24
 * Copyright (c) shuaikai. All rights reserved.
 */

#include <unordered_map>
#include <vector>
#include "lc.h"

using namespace std;

class Solution {
public:
    std::unordered_map<std::string, std::vector<std::string>> state_table{
        {}
    };

    int myAtoi(string s) {
    }
};

int main() {
    Solution su;
    print(su.myAtoi("  +0 123"));
    return 0;
}