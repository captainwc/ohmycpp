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

#define LOGGER  getLogger(getFileName(__FILE__, false), LOG)
#define ERROR   getLogger(getFileName(__FILE__, false), LOG_ERROR)
#define CONSOLE getLogger(getFileName(__FILE__, false), "")

#endif  // LOG_H