//
// 用二维矩阵模仿图片。类似leetcode中的岛屿的题目
//
// Created by shuaikai on 24-2-24.
//

#ifndef MODERNCPP_GRAPHIC_H
#define MODERNCPP_GRAPHIC_H

#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// 由于获取随机数的默认范围是 (0, 100)，因此此处设置中位数50作为划分
const int pivot = 50;

// 原样输出数组中的数字
const auto PRINT_INT = [](const int x) {
    printf("%2d ", x);
};

// 将数字数组转换为字符图形
const auto PRINT_CHAR_PIVOT = [](const int x) {
    printf("%c ", x < pivot ? '_' : '$');
};

// 针对01数组
const auto PRINT_CHAR_01 = [](const int x) {
    char elem = x == 0 ? '_' : (x == 1 ? '$' : '*');
    printf("%c ", elem);
};

// 将随机数数组转换为01
const auto CG_GRAPHIC_01 = [](std::vector<std::vector<int>>& sea) {
    std::for_each(sea.begin(), sea.end(), [](auto& vc) {
        std::transform(vc.begin(), vc.end(), vc.begin(), [](int x) {
            return x < pivot ? 0 : 1;
        });
    });
};

// 打印二维数组
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

// 可视化一维数组为dot文件
template <typename T>
void visualize1DArray(const std::vector<T>& array, const std::string& filename) {
    std::ofstream file(filename);
    file << "digraph G {\n";

    for (size_t i = 0; i < array.size(); ++i) {
        file << "  node" << i << " [label=\"" << array[i] << "\"];\n";
        if (i > 0) {
            file << "  node" << (i - 1) << " -> node" << i << ";\n";
        }
    }

    file << "}";
    file.close();
}

// 可视化二维数组为dot文件
template <typename T>
void visualize2DArray(const std::vector<std::vector<T>>& array, const std::string& filename) {
    std::ofstream file(filename);
    file << "digraph G {\n";

    for (size_t i = 0; i < array.size(); ++i) {
        for (size_t j = 0; j < array[i].size(); ++j) {
            file << "  node" << i << "_" << j << " [label=\"" << array[i][j] << "\"];\n";
            if (j > 0) {
                file << "  node" << i << "_" << (j - 1) << " -> node" << i << "_" << j << ";\n";
            }
            if (i > 0) {
                file << "  node" << (i - 1) << "_" << j << " -> node" << i << "_" << j << ";\n";
            }
        }
    }

    file << "}";
    file.close();
}

// 可视化一维数组为png文件
template <typename T>
void visualize1DArrayPNG(const std::vector<T>& array, const std::string& filename) {
    std::string dotFilename = filename + ".dot";
    visualize1DArray(array, dotFilename);

    std::string command = "dot -Tpng " + dotFilename + " -o " + filename;
    system(command.c_str());

    std::remove(dotFilename.c_str());
}

// 可视化二维数组为png文件
template <typename T>
void visualize2DArrayPNG(const std::vector<std::vector<T>>& array, const std::string& filename) {
    std::string dotFilename = filename + ".dot";
    visualize2DArray(array, dotFilename);

    std::string command = "dot -Tpng " + dotFilename + " -o " + filename;
    system(command.c_str());

    std::remove(dotFilename.c_str());
}

#endif  // MODERNCPP_GRAPHIC_H
