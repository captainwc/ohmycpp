/**
 * Create by shuaikai 2023/10/17 12:50:15
 *
 * Copyright (c) shuaikai. All rights reserved.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

enum LOGLEVEL{trace, info, debug, warn, critical, error};

class Logger {
public:
  template <typename... Args> void log(LOGLEVEL lvl, std::string fmt, Args &&...args) {
    std::stringstream ss;
    (ss << ... << std::forward<Args>(args));
    std::cout << "[LOG]: " << ss.str() << std::endl;
  }

};

#endif // LOGGER_H