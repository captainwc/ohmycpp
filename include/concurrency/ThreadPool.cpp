#include "ThreadPool.h"

#include <exception>

bool ThreadPool::addThread(int nums) {
    for (int i = 0; i < nums; i++) {
        if ((workingThreads_ + nums) > maxSize_) {
            return false;
        }
        if (!isRunning_) {
            throw std::runtime_error("ThreadPool has been ");
        }
        workers_.emplace_back([this]() {
            while (true) {
                TaskType task;
                {
                    std::unique_lock<std::mutex> lockGuard{mtx_};
                    cv_.wait(lockGuard, [this] {
                        return !isRunning_ || !tasks_.empty();
                    });
                    // NOTE: 为什么此处还要判空？
                    if (!isRunning_ && tasks_.empty()) {
                        return;
                    }
                    workingThreads_.fetch_add(1);
                    task = std::move(tasks_.front());
                    tasks_.pop();
                }
                task();

                // NOTE: 自动释放非核心线程
                if (workingThreads_ > coreSize_) {
                    std::unique_lock<std::mutex> lock{mtx_};
                    workers_.pop_back();
                }
            }
        });
    }
    return true;
}

ThreadPool::ThreadPool(int coreSize, int maxSize) : coreSize_(coreSize), maxSize_(maxSize), isRunning_(true) {
    if (!addThread(coreSize)) {
        throw std::runtime_error("Init ThreadPool Failed!");
    }
}

ThreadPool::~ThreadPool() {
    isRunning_.exchange(false);
    cv_.notify_all();
    for (auto &thread : workers_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

