#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });

    std::cout << "Thread " << id << " is working.\n";
}

int main() {
    std::thread t1(worker, 0);
    std::thread t2(worker, 1);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_all();

    t1.join();
    t2.join();
    
    return 0;
}