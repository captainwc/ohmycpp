#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include <iostream>
#include <list>
#include <map>
#include <set>
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

#endif  // PRINT_UTILS_H