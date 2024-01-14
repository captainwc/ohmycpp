/**
 * Create by shuaikai 2024/01/14 12:02:32
 *
 * Copyright (c) shuaikai. All rights reserved.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <filesystem>
#include <iostream>
#include <mutex>

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
    static std::mutex logMtx;
    std::filesystem::path path(filePath);
    std::string fileName = path.filename().string();
    // 输出时间： << "[" << time::getFormatTime().c_str() << "]"
    std::unique_lock<std::mutex> logLock(logMtx);
    switch (level) {
        case ERROR:
            std::cout << FC_RED << "[ERROR]" << FC_GREY << "[" << fileName.c_str() << ":" << funcName << ":" << line
                      << "] " << FC_RED;
            std::cout.flush();
            // printf(FC_RED);
            // printf("[%s][%s][%s:%s:%d] ", "ERROR", time::getFormatTime().c_str(), fileName.c_str(),
            // funcName, line);
            break;
        case WARN:
            std::cout << FC_YELLOW << "[WARN ]" << FC_GREY << "[" << fileName.c_str() << ":" << funcName << ":" << line
                      << "] " << FC_YELLOW;
            std::cout.flush();
            // printf(FC_YELLOW);
            // printf("[%s][%s][%s:%s:%d] ", "WARN ", time::getFormatTime().c_str(), fileName.c_str(), funcName, line);
            break;
        case DEBUG:
        default:
            std::cout << "[DEBUG]" << FC_GREY << "[" << fileName.c_str() << ":" << funcName << ":" << line << "] "
                      << ANSI_RESET;
            std::cout.flush();
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

#endif  // LOGGER_H