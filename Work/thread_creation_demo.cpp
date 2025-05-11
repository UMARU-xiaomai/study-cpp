#include <iostream>
#include <thread>
#include <chrono>

// 线程将执行的函数
void thread_function(int id) {
    std::cout << "线程 " << id << " 开始执行。" << std::endl;
    // 模拟一些工作
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::yield();//让出cpu时间片，不要与协程弄混了
    std::cout << "线程 " << id << " 执行完毕。" << std::endl;
}

int main() {
    std::cout << "主线程开始。" << std::endl;

    // 创建并启动一个新线程
    // std::thread t1(thread_function, 1);
    // 为了避免在某些编译器或环境下直接运行可执行文件时，
    // 由于主线程可能比新线程先结束而导致新线程的输出不完整或看不到，
    // 我们显式地创建线程对象，然后 join() 它。

    std::thread t1(thread_function, 1);
    std::thread t2(thread_function, 2);

    std::cout << "主线程创建了 t1 和 t2。" << std::endl;

    // 等待线程 t1 完成
    if (t1.joinable()) {
        t1.join();
        std::cout << "主线程：t1 已加入。" << std::endl;
    }

    // 等待线程 t2 完成
    if (t2.joinable()) {
        t2.join();
        std::cout << "主线程：t2 已加入。" << std::endl;
    }

    std::cout << "主线程结束。" << std::endl;

    return 0;
}

/*
编译和运行指南 (例如使用 g++):
1. 保存文件为 thread_creation_demo.cpp
2. 打开终端或命令行
3. 编译: g++ thread_creation_demo.cpp -o thread_demo -std=c++11 -pthread
   (注意: -pthread 标志对于链接 POSIX 线程库是必需的，在某些系统上可能不需要或有不同名称，如 MinGW 可能不需要显式链接)
4. 运行: ./thread_demo (在 Linux/macOS) 或 thread_demo.exe (在 Windows)
*/