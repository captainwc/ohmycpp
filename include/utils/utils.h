#ifndef MODERNCPP_UTILS_H
#define MODERNCPP_UTILS_H

#include <filesystem>
#include <random>

#include "print_utils.h"
#include "string_utils.h"

// 获取文件的basename，可以指定是否带有拓展名(With Extension)
std::string getFileName(const std::string& path, bool we) {
    std::filesystem::path p(path);
    if (we) {
        return p.filename().string();
    }
    return p.stem().string();
}

// 获取随机数
int get_random(int low = 0, int up = 100) {
    std::random_device                 rd;
    std::mt19937                       gen(rd());
    std::uniform_int_distribution<int> range(low, up);
    return range(gen);
}

// 获取随机int数组
auto get_vector(int n, int low = 0, int up = 100) {
    std::vector<int> ret(n);
    for (int i = 0; i < n; i++) {
        ret[i] = get_random(low, up);
    }
    return ret;
}

auto get_vector_2d(int x, int y, int low = 0, int up = 100) {
    std::vector<std::vector<int>> ret(x, std::vector<int>(y));
    for (int i = 0; i < x; i++) {
        ret[i] = get_vector(y, low, up);
    }
    return ret;
}

#endif  // MODERNCPP_UTILS_H
