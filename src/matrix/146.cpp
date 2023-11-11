#include <vector>

#include "algorithm/Utils.h"
#include "common.h"
#include "tree/TreeNode.h"

using namespace std;

class Solution {
public:
    vector<int> spiralArray(vector<vector<int>>& array) {
        // 空数组取array[0]时会越界
        if (array.empty())
            return {};

        vector<int> ret;

        int row = array.size();
        int col = array[0].size();

        int up = 0;
        int down = row - 1;
        int left = 0;
        int right = col - 1;

        while (ret.size() < row * col) {
            // left -> right
            if (up <= down) {
                for (int i = left; i <= right; i++) {
                    ret.push_back(array[up][i]);
                }
                up++;
            }
            // up -> down
            if (left <= right) {
                for (int i = up; i <= down; i++) {
                    ret.push_back(array[i][right]);
                }
                right--;
            }
            // right -> left;
            if (up <= down) {
                for (int i = right; i >= left; i--) {
                    ret.push_back(array[down][i]);
                }
                down--;
            }
            // down -> up
            if (left <= right) {
                for (int i = down; i >= up; i--) {
                    ret.push_back(array[i][left]);
                }
                left++;
            }
        }
        return ret;
    }

private:
};

int main() {
    vector<vector<int>> array = {{1, 2, 3, 4}, {8, 7, 6, 5}, {12, 11, 10, 9}, {16, 15, 14, 13}};
    Solution su;

    su.spiralArray(array);

    return 0;
}