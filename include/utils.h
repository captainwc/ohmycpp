#ifndef MODERNCPP_UTILS_H
#define MODERNCPP_UTILS_H

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

std::vector<std::string> split(const std::string& str, char delim) {
    std::stringstream        ss(str);
    std::vector<std::string> tokens;
    std::string              token;
    while (std::getline(ss, token, delim)) {
        tokens.emplace_back(token);
    }
    return tokens;
}

#endif  // MODERNCPP_UTILS_H
