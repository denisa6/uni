#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::vector<int> vector1 = { 1, 2, 3, 4, 5};
std::vector<int> vector2 = { 10, 20, 30, 40, 50};
std::queue<int> products;

std::mutex mtx;
std::condition_variable cv;
int result = 0;

void producer() {
    int product;
    for (int i = 0; i < vector1.size(); i++) {
        std::unique_lock<std::mutex> lock(mtx);
        product = vector1[i] * vector2[i];
        std::cout << "produced = " << product << std::endl;
        products.push(product);
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consumer() {
    for (int i = 0; i < vector1.size(); i++) {
        std::unique_lock<std::mutex> lock(mtx);
        while (products.empty()) {
            std::cout << "thread with id " << std::this_thread::get_id() << " : buffer is currently empty" << "\n";
            cv.wait(lock);
        }
        result += products.front();
        products.pop();
        std::cout << "consumed = " << result << "\n";
    }
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    std::cout << std::endl << "final product = " << result << std::endl;

    return 0;
}
