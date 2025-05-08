#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

// 共享资源类 / Shared Resource Class
// 这个类演示了如何使用互斥锁保护共享数据
// 概要：
// 1. 将 std::mutex 与要保护的资源（共享计数器）封装在SharedCounter 类中
// 2. 使用 std::lock_guard 确保在函数结束时自动解锁
// 3. 这样，在 SharedCounter 类中，所有对共享计数器的操作都是线程安全的
// This class demonstrates how to protect shared data using mutex
class SharedCounter {
private:
    int counter = 0;  // 共享计数器 / Shared counter
    std::mutex mtx;   // 互斥锁 / Mutex for synchronization

public:
    // 增加计数器的值 / Increment the counter value
    // 使用 std::lock_guard 确保在函数结束时自动解锁
    // Using std::lock_guard to ensure automatic unlocking when function ends
    void increment() {
        std::lock_guard<std::mutex> lock(mtx);  // ##关键## RAII风格的锁 / RAII-style locking
        counter++;
        std::cout << "Counter value: " << counter << std::endl;
    }

    // 获取当前计数器的值 / Get the current counter value
    // 同样使用互斥锁保护读取操作
    // Also using mutex to protect read operation
    int getValue() {
        std::lock_guard<std::mutex> lock(mtx);
        return counter;
    }
};

// 工作线程函数 / Worker thread function
// 每个线程将执行指定次数的计数器增加操作
// Each thread will perform the specified number of counter increments
void worker(SharedCounter& counter, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counter.increment();
        // 添加短暂延迟，模拟实际工作负载
        // Add a small delay to simulate real workload
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// 安全银行账户类 / Safe Bank Account Class
// 演示如何防止死锁 / Demonstrates how to prevent deadlocks
class SafeBankAccount {
private:
    int balance;
    std::mutex mtx;

public:
    SafeBankAccount(int initial_balance) : balance(initial_balance) {}

    // 使用 std::lock 和 std::unique_lock 来防止死锁
    // Using std::lock and std::unique_lock to prevent deadlocks
    static void transfer(SafeBankAccount& from, SafeBankAccount& to, int amount) {

        // ##关键## 使用 std::lock 和 std::unique_lock 来防止死锁
        // 创建两个 unique_lock，但暂时不锁定
        // Create two unique_locks but don't lock them yet
        std::unique_lock<std::mutex> lock1(from.mtx, std::defer_lock);
        std::unique_lock<std::mutex> lock2(to.mtx, std::defer_lock);
        //std::defer_lock: 创建但不锁定
        //std::try_to_lock: 尝试锁定
        //std::adopt_lock: 假设已经锁定

        // 使用 std::lock 同时锁定两个互斥量，避免死锁
        // Use std::lock to lock both mutexes simultaneously, avoiding deadlock
        std::lock(lock1, lock2);
        // 常见死锁防止方法：
        // 1.总是以相同的顺序获取锁（比如按照内存地址排序）
        // 2.使用 std::lock 来同时获取多个锁

        // 执行转账操作 / Perform transfer
        from.balance -= amount;
        to.balance += amount;
        // 演示手动解锁（实际不需要） / Demonstrate manual unlocking (not actually needed)
        std::unique_lock<std::mutex> lock1(from.mtx, std::defer_lock);
        std::unique_lock<std::mutex> lock2(to.mtx, std::defer_lock);

        std::cout << "Transfer completed: " << amount << std::endl;
    }

    int getBalance() {
        std::lock_guard<std::mutex> lock(mtx);
        return balance;
    }
};

// 转账工作线程函数 / Transfer worker thread function
void transferWorker(SafeBankAccount& account1, SafeBankAccount& account2, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        SafeBankAccount::transfer(account1, account2, 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    // 创建共享计数器实例 / Create shared counter instance
    SharedCounter counter;
    
    // 存储线程的向量 / Vector to store threads
    std::vector<std::thread> threads;
    
    // 配置参数 / Configuration parameters
    const int num_threads = 3;           // 线程数量 / Number of threads
    const int iterations_per_thread = 5; // 每个线程的操作次数 / Operations per thread

    // 创建并启动多个线程 / Create and start multiple threads
    for (int i = 0; i < num_threads; ++i) {
        // 使用 std::ref 传递计数器的引用
        // Use std::ref to pass counter by reference
        threads.emplace_back(worker, std::ref(counter), iterations_per_thread);
    }

    // 等待所有线程完成 / Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }

    // 输出最终结果 / Output final result
    std::cout << "Final counter value: " << counter.getValue() << std::endl;

    // 死锁防止示例 / Deadlock prevention example
    std::cout << "\nDemonstrating deadlock prevention:" << std::endl;
    
    SafeBankAccount account1(1000);
    SafeBankAccount account2(1000);
    
    std::vector<std::thread> transferThreads;
    
    // 创建两个线程，一个从account1转到account2，另一个从account2转到account1
    // Create two threads, one transferring from account1 to account2, another from account2 to account1
    transferThreads.emplace_back(transferWorker, std::ref(account1), std::ref(account2), 3);
    transferThreads.emplace_back(transferWorker, std::ref(account2), std::ref(account1), 3);

    for (auto& thread : transferThreads) {
        thread.join();
    }

    std::cout << "Final balance of account1: " << account1.getBalance() << std::endl;
    std::cout << "Final balance of account2: " << account2.getBalance() << std::endl;

    return 0;
}
