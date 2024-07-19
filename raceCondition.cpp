#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx; 
int counter = 0; 

void incrementCounter(int id) {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }
    std::cout << "Thread " << id << " finished.\n";
}

int main() {
    const int numThreads = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(incrementCounter, i));
    }

    for (auto& th : threads) {
        th.join();
    }

    std::cout << "Final counter value: " << counter << "\n";
    return 0;
}