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

#include <cctype>
#include <chrono>
#include <cstdint>
#include <ostream>
#include <thread>
#include <unordered_map>
#include <vector>

#include "lc.h"
#include "log.h"

using namespace std;

enum class State {
    START,
    IN_NUM,
    SIGNED,
    END
};

class Solution {
    // num, space, +/-, other
    std::unordered_map<State, std::vector<State>> transform_table{
        {State::START, {State::IN_NUM, State::START, State::SIGNED, State::END}},
        {State::IN_NUM, {State::IN_NUM, State::END, State::END, State::END}},
        {State::SIGNED, {State::IN_NUM, State::END, State::END, State::END}},
        {State::END, {State::END, State::END, State::END, State::END}}};

    State   state_ = State::START;
    int64_t ret_   = 0;
    int8_t  sign_  = 1;

    int get_transiction(char token) {
        if (isdigit(token)) {
            return 0;
        } else if (isspace(token)) {
            return 1;
        } else if (token == '+' || token == '-') {
            return 2;
        } else {
            return 3;
        }
    }

    void transformer(char token) {
        state_ = transform_table[state_][get_transiction(token)];
        if (state_ == State::IN_NUM) {
            ret_ = ret_ * 10 + token - '0';
            ret_ = sign_ == 1 ? min(ret_, (int64_t)INT32_MAX) : min(ret_, -(int64_t)INT32_MIN);
        } else if (state_ == State::SIGNED) {
            sign_ = token == '+' ? 1 : -1;
        } else {
            // do nothing
        }
    }

public:
    int myatoi(string s) {
        for (char c : s) {
            transformer(c);
        }
        return ret_ * sign_;
    }
};

int main(int argc, char* argv[]) {
    Solution su;
    if (argc == 1) {
        print(su.myatoi(" +123 4 "));
    } else {
        print(su.myatoi(argv[1]));
    }
    return 0;
}