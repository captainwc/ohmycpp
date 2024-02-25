/*
 * @lc app=leetcode.cn id=9 lang=cpp
 *
 * [9] 回文数
 */

// @lc code=start
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        int tmp = x;
        if (x < 0) {
            return false;
        }
        long long y = 0;
        while (x > 0) {
            int last = x % 10;
            x /= 10;
            y = y * 10 + last;
        }
        return tmp == y;
    }
};

int main() {
    Solution su;
    cout << su.isPalindrome(121) << endl;
}

// @lc code=end
