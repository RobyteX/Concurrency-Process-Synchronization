#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;

void thread1() {
    std::unique_lock<std::mutex> lock1(mutex1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    std::unique_lock<std::mutex> lock2(mutex2);
    std::cout << "Thread 1 acquired both mutexes." << std::endl;
}

void thread2() {
    std::unique_lock<std::mutex> lock1(mutex1); 
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    std::unique_lock<std::mutex> lock2(mutex2);
    std::cout << "Thread 2 acquired both mutexes." << std::endl;
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}