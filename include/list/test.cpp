#include <chrono>
#include <iostream>
#include <mutex>
#include <numeric>
#include <ratio>
#include <thread>

int x = 1;
int y = 1;

void do_work_x() {
    static std::mutex mtx;
    while (x < 100) {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << x++ << " | ";
        std::cout.flush();
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void do_work_y() {
    while (y < 100) {
        std::cout << y++ << " @ ";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread t1(do_work_x);
    // std::thread t2(do_work_y);
    std::thread t3(do_work_x);
    // std::thread t4(do_work_y);

    t1.join();
    // t2.join();
    t3.detach();
    // t4.detach();

    return 0;
}