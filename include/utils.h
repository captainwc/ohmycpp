#ifndef MODERNCPP_UTILS_H
#define MODERNCPP_UTILS_H

#include <filesystem>

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

#endif  // MODERNCPP_UTILS_H
