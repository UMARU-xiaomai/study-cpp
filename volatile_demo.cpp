#include <iostream>
#include <thread>
#include <chrono>

// 全局变量
volatile bool flag = false;

// 线程函数：修改flag
void setFlag() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    flag = true;
    std::cout << "Flag has been set to true" << std::endl;
}

// 线程函数：检查flag
void checkFlag() {
    while (!flag) {
        // 如果没有volatile关键字，编译器可能会优化掉这个循环
        // 因为编译器认为flag的值不会改变
        std::cout << "Waiting for flag..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "Flag is now true!" << std::endl;
}

int main() {
    std::cout << "Starting volatile demonstration..." << std::endl;
    
    // 创建两个线程
    std::thread t1(setFlag);
    std::thread t2(checkFlag);
    
    // 等待线程完成
    t1.join();
    t2.join();
    
    std::cout << "Demonstration completed." << std::endl;
    return 0;
} 