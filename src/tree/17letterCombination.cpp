/**
 * BRIEF: 输入一串数字代表九键盘的数字，输出所有可能的字母组合
 *
 * IDEA: 回溯
 *
 * LINK: https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
 *
 * Create by shuaikai 2023/12/27 22:12:28
 * Copyright (c) shuaikai. All rights reserved.
 */

#include <vector>

#include "algorithm/Utils.h"
#include "common.h"

using namespace std;

class Solution {
public:
    vector<string> keymap{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ret;
    string str;

    vector<string> letterCombinations(string digits) {
        travsal(0, digits);
        return ret;
    }

    void travsal(int pos, string digits) {
        // 终止选择：在叶子处终止
        if (pos == digits.length()) {
            if (str != "") {
                ret.push_back(str);
            }
            return;
        }
        // 在pos位置对应的树层，进行选择
        string keys = keymap[digits[pos] - 48];
        for (int i = 0; i < keys.length(); i++) {
            //* (1) 选择第i条路
            str.push_back(keys[i]);
            travsal(pos + 1, digits);
            //* (2) 回溯，不选第 i 条路了，准备选第 i + 1 条
            str.pop_back();
        }
    }
};

int main() {
    Solution su;

    vector<string> ret = su.letterCombinations("23");
    printVector(ret);

    return 0;
}
