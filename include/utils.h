#ifndef MODERNCPP_UTILS_H
#define MODERNCPP_UTILS_H

#include <filesystem>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
concept LinerList =
    std::same_as<T, std::vector<typename T::value_type>> || std::same_as<T, std::list<typename T::value_type>>
    || std::same_as<T, std::set<typename T::value_type>> || std::same_as<T, std::unordered_set<typename T::value_type>>;

template <typename T>
concept Map = std::same_as<T, std::map<typename T::key_type, typename T::mapped_type>>
              || std::same_as<T, std::unordered_map<typename T::key_type, typename T::mapped_type>>;

template <typename T>
concept Printable = requires(T elem) {
    { std::cout << elem };
};

// 通用打印
template <Printable T>
void print(T elem, char delim = '\n') {
    std::cout << elem << delim;
}

//  打印线性容器
template <LinerList T>
void print(T list, const std::string& str = "") {
    if (!str.empty()) {
        std::cout << str << " ";
    }
    for (auto x : list) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// 打印关联容器
template <Map T>
void print(T map, const std::string& str = "") {
    if (!str.empty()) {
        std::cout << str << " ";
    }
    for (auto entry : map) {
        std::cout << "<" << entry.first << "," << entry.second << "> ";
    }
    std::cout << std::endl;
}

// 分割字符串
std::vector<std::string> split(const std::string& str, char delim) {
    std::stringstream        ss(str);
    std::vector<std::string> tokens;
    std::string              token;
    while (std::getline(ss, token, delim)) {
        tokens.emplace_back(token);
    }
    return tokens;
}

// 获取文件的basename，可以指定是否带有拓展名(With Extension)
std::string getFileName(const std::string& path, bool we) {
    std::filesystem::path p(path);
    if (we) {
        return p.filename().string();
    }
    return p.stem().string();
}

// 字符串转整数
int64_t stoi_mine(const std::string& str) {
    std::istringstream ss(str);

    bool    stopped    = false;
    bool    can_signed = true;
    bool    can_space  = true;
    char    sign       = '+';
    int64_t ret        = 0;
    char    token;

    while (!stopped && ss >> token) {
        switch (token) {
            case '+':
            case '-':
                if (can_signed) {
                    can_signed = false;
                    can_space  = false;
                    sign       = token;
                } else {
                    stopped = true;
                }
                break;
            case ' ':
                if (!can_space) {
                    stopped = true;
                }
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                ret = ret * 10 + (token - '0');
                break;
            default:
                stopped = true;
                break;
        }
    }
    if (ret == 0) {
        return 0;
    }
    if (sign == '-') {
        return ~ret + 1;
    }
    return ret;
}

#endif  // MODERNCPP_UTILS_H
