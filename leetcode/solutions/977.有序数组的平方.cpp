/*
 * @lc app=leetcode.cn id=977 lang=cpp
 *
 * [977] 有序数组的平方
 */

#include "leetcode/lc.h"

// @lc code=start
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        transform(nums.begin(), nums.end(), nums.begin(), [](int x) {
            return x * x;
        });
        sort(nums.begin(), nums.end());
        return nums;
    }
};

// @lc code=end
int main(int argc, char const* argv[]) {
    Solution su;
    auto     vc = get_vector(10);
    print(vc);
    return 0;
}