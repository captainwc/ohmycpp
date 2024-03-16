#include <iostream>

#include "ThreadPool.h"

auto f1 = [](int x, int y) {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "f1: " << x + y << std::endl;
};

class F2 {
    void operator()(int x, int y) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "f2: " << x * y << std::endl;
    }
};

int main() {
    ThreadPool pool(4);
    F2         f2;
    pool.submit(f1, 10, 20);
    pool.submit(f1, 20, 30);
    pool.submit(f1, 30, 40);
    pool.submit(f1, 40, 50);
}