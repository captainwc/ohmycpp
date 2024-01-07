//
// Created by j50036120 on 2023/9/28.
//

#ifndef LEETCODE_CPP_UTILS_H
#define LEETCODE_CPP_UTILS_H

#include <locale.h>
#include <unistd.h>

#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <regex>
#include <string>
#include <vector>

#include "list/ListNode.h"  // 提供 List utils

namespace utils {

// 这把锁放在头文件里有问题吗？
std::mutex util_mtx;

//==-------------------- ANSI -----------------------==//

#define ANSI_RESET "\033[0m"
#define FC_RED     "\033[31m"
#define FC_GREEN   "\033[32m"
#define FC_YELLOW  "\033[33m"
#define FC_GREY    "\033[90m"

enum COLOR {
    RED,
    GREEN,
    YELLOW
};

//==--------------------- Time ----------------------==//
namespace time {
inline std::string getFormatTime(const char* format = "%Y-%m-%d %H:%M:%S") {
    // 获取当前系统时间
    auto now = std::chrono::system_clock::now();
    // 将时间转换为时间结构体
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    // 格式化时间并输出
    std::stringstream ss;
    ss << std::put_time(std::localtime(&currentTime), format);
    return ss.str();
}
}  // namespace time

//==----------------- Progress Bar ------------------==//

inline void progressBar(int p, int total, const char* msg = "", int width = 49) {
    printf("\033[s\033[H\033[0m");
    int x = p;
    int y = total;
    double pre = static_cast<double>(p);
    if (total > width) {
        pre = pre / (static_cast<double>(total) / width);
        total = width;
    }

    setlocale(LC_ALL, "");
    if (pre > total || std::abs(total - pre) < 1e-6) {
        printf("\033[?25I\033[32m【%s \u25c9 FINSH】\033[0m", msg);
        printf("\033[u\033[0m");
        printf("\r");
        printf("\033[?25I\033[32m【%s \u25c9 FINSH】\033[0m", msg);
        fflush(stdout);
        return;
    }

    printf("\r");
    printf("\033[?25I\033[31m【%s %6.2lf%%】\033[0m", msg, pre / total * 100.0);
    for (int i = 0; i < total; i++) {
        printf("\u2593");
    }
    // printf("[%4d/%4d]", x, y);
    fflush(stdout);

    printf("\r");
    printf("\033[?25I\033[31m【%s %6.2lf%%】\033[0m", msg, pre / total * 100.0);
    for (int i = 0; i < pre; i++) {
        printf("\u2588");
    }
    fflush(stdout);
    printf("\033[u\033[0m");
}

//==--------------------- Log ----------------------==//
namespace log {
enum LEVEL {
    DEBUG,
    WARN,
    ERROR
};

#define LOG(level, format, ...) utils::log::logWithPos(level, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define ERROR(format, ...)      LOG(utils::log::ERROR, format, ##__VA_ARGS__)
#define DEBUG(format, ...)      LOG(utils::log::DEBUG, format, ##__VA_ARGS__)
#define WARN(format, ...)       LOG(utils::log::WARN, format, ##__VA_ARGS__)

// TODO 新增 log 到文件
// TODO 把c++哪个什么forward传递参数的给整明白，tnnd，一定要写出一个能输出位置的日志函数
inline void logWithPos(LEVEL level, const char* filePath, const char* funcName, int line, const char* format, ...) {
    std::filesystem::path path(filePath);
    std::string fileName = path.filename().string();
    // 输出时间： << "[" << time::getFormatTime().c_str() << "]"
    std::unique_lock<std::mutex> logLock(util_mtx);
    switch (level) {
        case ERROR:
            std::cout << FC_RED << "[ERROR]" << FC_GREY << "[" << fileName.c_str() << ":" << funcName << ":" << line
                      << "] " << FC_RED;
            // printf(FC_RED);
            // printf("[%s][%s][%s:%s:%d] ", "ERROR", time::getFormatTime().c_str(), fileName.c_str(),
            // funcName, line);
            break;
        case WARN:
            std::cout << FC_YELLOW << "[WARN ]" << FC_GREY << "[" << fileName.c_str() << ":" << funcName << ":" << line
                      << "] " << FC_YELLOW;
            // printf(FC_YELLOW);
            // printf("[%s][%s][%s:%s:%d] ", "WARN ", time::getFormatTime().c_str(), fileName.c_str(), funcName, line);
            break;
        case DEBUG:
        default:
            std::cout << "[DEBUG]" << FC_GREY << "[" << fileName.c_str() << ":" << funcName << ":" << line << "] "
                      << ANSI_RESET;
            // printf("[%s][%s][%s:%s:%d] ", "DEBUG", time::getFormatTime().c_str(), fileName.c_str(), funcName, line);
            break;
    }
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf(ANSI_RESET);
    putchar('\n');
    logLock.unlock();
}

// template <typename... Args>
// inline void log(log::LEVEL level, const char* format, Args... args) {
//     logWithPos(level, "", "", 0, format, args...);
// }
}  // namespace log

//==-------------------- Print ----------------------==//
namespace printer {
template <typename T>
std::string vector2String(const std::vector<T>& vc) {
    std::string ret = "[";
    for (auto x : vc) {
        ret.append(x);
        ret.append(",");
    }
    ret.pop_back();
    return ret.append("]");
}

inline std::string list2String(const ListNode* head) {
    auto pNode = head;
    std::string str = "[";
    while (pNode != nullptr) {
        str.append(std::to_string(pNode->val) + ",");
        pNode = pNode->next;
    }
    str.pop_back();
    str.append("]");
    return str;
}

inline std::string list2String(const LinkList& list) {
    return list2String(list.head());
}

template <typename T>
void printVector(const std::vector<T>& vc) {
    std::cout << vector2String(vc) << std::endl;
}

inline void printLinkList(const ListNode* head) {
    std::cout << list2String(head) << std::endl;
}

inline void printLinkList(const LinkList& list) {
    printLinkList(list.front());
}
}  // namespace printer

//==----------------- String Op ---------------------==//
namespace str {
inline std::vector<std::string> splitString(std::string str, std::string sep) {
    std::regex re(sep);
    std::sregex_token_iterator p(str.begin(), str.end(), re, -1);
    std::sregex_token_iterator end;
    std::vector<std::string> vec(p, end);
    return vec;
}
}  // namespace str

//==----------------- LinkList ----------------------==//
namespace list {
inline LinkList getLinkList(std::string str) {
    auto ret = str::splitString(str, ",");
    LinkList list;
    for (auto st : ret) {
        list.push_back(std::stoi(st));
    }
    return list;
}
}  // namespace list
}  // namespace utils

#endif  // LEETCODE_CPP_UTILS_H
