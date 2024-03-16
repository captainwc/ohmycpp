#ifndef OHMYCPP_THREADPOOL_H
#define OHMYCPP_THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

/**
 * 线程池：
 */
class ThreadPool {
public:
    using TaskType = std::function<void()>;

public:
    static const int MAX_SIZE = 16;

public:
    explicit ThreadPool(int coreSize, int maxSize = MAX_SIZE);
    ~ThreadPool();

    template <typename Fn, typename... Args>
    auto submit(Fn &&f, Args &&...args) -> std::future<decltype(f(args...))>;

    ThreadPool(ThreadPool &)            = delete;
    ThreadPool(ThreadPool &&)           = delete;
    ThreadPool operator=(ThreadPool &)  = delete;
    ThreadPool operator=(ThreadPool &&) = delete;

private:
    bool addThread(int);

private:
    std::atomic<bool>                 isRunning_;
    std::atomic<int>                  coreSize_;        // 线程池核心线程数
    std::atomic<int>                  maxSize_;         // 线程池上限
    std::atomic<int>                  workingThreads_;  // 工作线程数
    std::mutex                        mtx_;
    std::condition_variable           cv_;
    std::vector<std::thread>          workers_;
    std::queue<std::function<void()>> tasks_;
};

template <typename Fn, typename... Args>
auto ThreadPool::submit(Fn &&f, Args &&...args) -> std::future<decltype(f(args...))> {
    using RetType    = decltype(f(args...));
    using FuncType   = std::function<RetType()>;
    using ResultType = std::future<RetType>;

    FuncType   func    = std::bind(std::forward<Fn>(f), std::forward<Args>(args)...);
    auto       taskPtr = std::make_shared<std::packaged_task<FuncType>>(func);
    ResultType result  = taskPtr->get_future();

    TaskType wrappedTask = [taskPtr]() {
        (*taskPtr)();
    };
    {
        std::unique_lock<std::mutex> lock{mtx_};
        tasks_.emplace(wrappedTask);
    }

    if (workingThreads_ > coreSize_) {
        addThread(1);
    }

    cv_.notify_one();
    return result;
}

#endif  // OHMYCPP_THREADPOOL_H
