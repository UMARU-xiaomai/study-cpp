// extern_usage.cpp
#include <iostream>

// 使用 extern 声明在其他文件中定义的全局变量
extern int global_variable;

// 使用 extern 声明在其他文件中定义的函数
extern void display_message();

int main() {
    std::cout << "--- In extern_usage.cpp --- " << std::endl;

    // 使用外部定义的全局变量
    std::cout << "Global variable from extern_definition.cpp: " << global_variable << std::endl;

    // 调用外部定义的函数
    display_message();

    // 修改外部定义的全局变量 (可选，演示其可写性)
    global_variable = 200;
    std::cout << "Global variable modified in extern_usage.cpp to: " << global_variable << std::endl;

    std::cout << "--- Leaving extern_usage.cpp --- " << std::endl;
    return 0;
}