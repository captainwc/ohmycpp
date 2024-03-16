#ifndef COMMON_H
#define COMMON_H

#include <memory>
#include <mutex>

#define GCTX GlobalContext::getInstance()

// Meyers’ Singleton：单例模式局部静态变量实现
class GlobalContext {
public:
    std::string WORK_SPACE;

public:
    static GlobalContext& getInstance() {
        static GlobalContext instance;
        instance.init();
        return instance;
    }

    GlobalContext(const GlobalContext&)            = delete;
    GlobalContext& operator=(const GlobalContext&) = delete;

private:
    void init() {
        WORK_SPACE = "/home/shuaikai/projects/develop/leetcode/leetcode-cpp/";
    }

private:
    GlobalContext() = default;
};

#endif  // COMMON_H