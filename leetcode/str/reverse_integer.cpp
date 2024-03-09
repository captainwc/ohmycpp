/**
 * BRIEF: 反转整数，中间不能使用超过INT范围的结果
 *
 * IDEA: 别怕原始，就老老实实通过取余和乘10进行移动就行了
 *
 * Create by shuaikai 2024/02/22 19:00:15
 * Copyright (c) shuaikai. All rights reserved.
 */

#include <cstdint>

#include "leetcode/lc.h"
#include "utils/print_utils.h"

using namespace std;
#define int int32_t

class Solution {
public:
    static int reverse(int x) {
        int ret = 0;
        while (x != 0) {
            if (ret < INT32_MIN / 10 || ret > INT32_MAX / 10) {
                return 0;
            }
            int last = x % 10;
            x /= 10;
            ret = ret * 10 + last;
        }
        return ret;
    }
};

int main() {
    Solution su;
    print(su.reverse(INT16_MIN));
    return 0;
}