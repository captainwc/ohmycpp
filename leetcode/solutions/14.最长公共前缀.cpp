/*
 * @lc app=leetcode.cn id=14 lang=cpp
 *
 * [14] 最长公共前缀
 */

#include "leetcode/lc.h"

// @lc code=start
class Solution {
public:
    string longestCommonPrefix(const vector<string>& strs) {
        string ret     = "";
        int    i       = 0;
        bool   stopped = false;

        while (!stopped) {
            char c    = '#';
            bool pass = false;
            for (string str : strs) {
                if (i >= str.size()) {
                    stopped = true;
                    break;
                }
                if (c == '#') {
                    c = str[i];
                }
                pass = str[i] == c;
                if (!pass) {
                    break;
                }
            }
            if (stopped) {
                break;
            } else if (pass) {
                i++;
                ret.push_back(c);
            } else {
                stopped = true;
            }
        }
        return ret;
    }
};

// @lc code=end

int main(int argc, char const* argv[]) {
    Solution su;
    cout << su.longestCommonPrefix({"ab", "a"});
    return 0;
}