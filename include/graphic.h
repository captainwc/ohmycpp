//
// Created by shuaikai on 24-2-24.
//

#ifndef MODERNCPP_GRAPHIC_H
#define MODERNCPP_GRAPHIC_H

#include <functional>
#include <iostream>
#include <vector>

const auto PRINT_INT = [](const int x) {
    printf("%2d ", x);
};

const auto PRINT_CHAR = [](const int x) {
    printf("%c ", x < 50 ? '_' : '$');
};

void show_graphic(const std::vector<std::vector<int>>&  graphic,
                  const std::function<void(const int)>& printer = PRINT_INT) {
    auto col_num = graphic[0].size();
    auto row_num = graphic.size();
    for (int i = 0; i < row_num; i++) {
        for (int j = 0; j < col_num; j++) {
            std::invoke(printer, graphic[i][j]);
        }
        putchar('\n');
    }
}

#endif  // MODERNCPP_GRAPHIC_H
