/**
 一个对spdlog的封装，可直接获得一个名字为当前文件加函数名的logger

 定义了一个map，存储所有的logger，通过文件名和日志名作为键，来查找存在的logger
 如果存在则返回，否则新建一个，存储后返回
 这样做是为了防止重名logger的出现

 @usage: LOGGER \ ERROR \ CONSOLE
 @auther: shuaikai
 @date: 2024/02/22
*/

#ifndef LOG_H
#define LOG_H

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

#include "common.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "utils.h"

const std::string LOG       = WORKSPACE + "log/log.log";
const std::string LOG_ERROR = WORKSPACE + "log/error.log";

std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> LOGGERS;

auto getLogger(const std::string& name, const std::string& file) {
    if (LOGGERS.find(name + file) != LOGGERS.end()) {
        return LOGGERS[name + file];
    }
    std::shared_ptr<spdlog::logger> logger;
    if (file.empty()) {
        logger = spdlog::stdout_color_mt(name);
    } else {
        std::filesystem::path log_file(file);
        logger = spdlog::basic_logger_mt(name + "_" + log_file.stem().string(), file);
    }
    LOGGERS[name + file] = logger;
    return logger;
}

#define GET_LOGGER_NAME getFileName(__FILE__, false) + "::" + __FUNCTION__
#define LOGGER          getLogger(GET_LOGGER_NAME, LOG)
#define ERROR           getLogger(GET_LOGGER_NAME, LOG_ERROR)
#define CONSOLE         getLogger(GET_LOGGER_NAME, "")

#endif  // LOG_H