#include <iostream>
#include <coroutine>
#include <future>
#include <chrono>

// Task结构体：定义协程的返回类型
// 每个协程函数必须返回一个包含promise_type的类型
struct Task {
    // promise_type：协程的核心控制结构
    // 它定义了协程的行为和状态管理
    struct promise_type {
        // 创建并返回Task对象
        // 当协程函数被调用时，编译器会调用这个函数
        Task get_return_object() { 
            return Task(std::coroutine_handle<promise_type>::from_promise(*this)); 
        }

        // 定义协程初始挂起点
        // suspend_always表示协程创建后立即挂起
        // 这让我们可以在协程开始执行前做一些准备工作
        std::suspend_always initial_suspend() { return {}; }

        // 定义协程最终挂起点
        // 协程完成时是否挂起
        // 这里选择挂起，这样我们可以检查协程的完成状态
        std::suspend_always final_suspend() noexcept { return {}; }

        // 当协程使用co_return返回void时调用
        void return_void() {}

        // 处理协程中未捕获的异常
        // 这里简单地终止程序，实际应用中可能需要更复杂的错误处理
        void unhandled_exception() { std::terminate(); }
    };

    // 构造函数：接收协程句柄
    // 句柄用于控制协程的生命周期
    Task(std::coroutine_handle<promise_type> h) : handle(h) {}

    // 禁止拷贝构造，防止多个Task对象共享同一个协程句柄
    Task(const Task&) = delete;

    // 移动构造函数：允许Task对象的所有权转移
    // 移动后原对象的句柄被设置为nullptr
    Task(Task&& other) noexcept : handle(other.handle) { 
        other.handle = nullptr; 
    }

    // 析构函数：确保协程句柄被正确销毁
    // 防止内存泄漏
    ~Task() { 
        if (handle) handle.destroy(); 
    }

    // 恢复协程执行的方法
    // 当协程被挂起时，调用此方法可以继续执行
    void resume() { 
        if (handle) handle.resume(); 
    }

    // 存储协程句柄
    // 用于控制协程的生命周期和执行
    std::coroutine_handle<promise_type> handle;
};

// 一个简单的异步函数
Task async_function() {
    std::cout << "开始异步操作...\n";
    co_await std::suspend_always{};
    std::cout << "异步操作完成！\n";
}

// 一个带有延迟的异步函数
Task delayed_function() {
    std::cout << "开始延迟操作...\n";
    co_await std::suspend_always{};
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "延迟操作完成！\n";
}

int main() {
    std::cout << "主函数开始\n";
    
    // 创建协程任务
    Task task1 = async_function();
    Task task2 = delayed_function();
    
    std::cout << "主函数继续执行\n";
    
    // 手动恢复协程执行
    task1.resume();
    task2.resume();
    
    // 等待一段时间以确保所有输出都能看到
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "主函数结束\n";
    return 0;
} 