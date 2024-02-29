#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <sstream>
#include <string>
#include <vector>

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

// --- 格式化字符串，展开参数包最后一步
template <typename T>
void _format_string_helper(std::stringstream& ss, const std::string& format, T&& arg) {
    static std::string placeholder = "{}";

    auto pos = format.find(placeholder);
    if (pos != std::string::npos) {
        ss << format.substr(0, pos) << arg << format.substr(pos + placeholder.size());
    }
}

// --- 格式化字符串， 递归展开参数包
template <typename T, typename... Args>
static void _format_string_helper(std::stringstream& ss, const std::string& format, T&& arg, Args&&... args) {
    static std::string placeholder = "{}";

    auto pos = format.find(placeholder);
    if (pos != std::string::npos) {
        ss << format.substr(0, pos) << arg;
        _format_string_helper(ss, format.substr(pos + placeholder.size()), std::forward<Args>(args)...);
    }
}

// 格式化字符串，将参数替换format中的{}，如果数量不匹配则报错
template <typename... Args>
std::string format_string(const std::string& format, Args&&... args) noexcept {
    std::stringstream ss;
    _format_string_helper(ss, format, std::forward<Args>(args)...);
    return ss.str();
}

#endif  // STRING_UTILS_H