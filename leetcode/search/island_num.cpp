//
// Created by shuaikai on 24-2-25.
//

#include "graphic/graphic.h"
#include "utils/utils.h"

using GRAPHIC = std::vector<std::vector<int>>;

class Solution {
public:
    static void flood(GRAPHIC& sea, int x, int y) {
        auto col = sea[0].size();
        auto row = sea.size();
        if (x < 0 || x >= col || y < 0 || y >= row) {
            return;
        }
        if (sea[x][y] == -1 || sea[x][y] == 0) {
            return;
        }

        sea[x][y] = -1;
        flood(sea, x - 1, y);
        flood(sea, x, y + 1);
        flood(sea, x + 1, y);
        flood(sea, x, y - 1);
    }

    static int get_island_num(GRAPHIC& sea) {
        int cnt = 0;
        for (int x = 0; x < sea.size(); x++) {
            for (int y = 0; y < sea[0].size(); y++) {
                if (sea[x][y] == 1) {
                    cnt++;
                    flood(sea, x, y);
                }
            }
        }
        return cnt;
    }
};

int main() {
    auto sea = get_vector_2d(10, 10);
    std::invoke(CG_GRAPHIC_01, sea);
    show_graphic(sea, PRINT_CHAR_01);
    std::cout << Solution::get_island_num(sea) << std::endl;
    show_graphic(sea, PRINT_CHAR_01);
}