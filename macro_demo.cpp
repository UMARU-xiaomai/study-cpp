#include <iostream>

// 基本宏定义
#define PI 3.14159
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 多行宏定义
#define PRINT_INFO(name, age) \
    std::cout << "Name: " << name << std::endl; \
    std::cout << "Age: " << age << std::endl

// 条件编译宏
#define DEBUG 1

int main() {
    // 使用基本宏
    std::cout << "PI = " << PI << std::endl;
    std::cout << "Square of 5 = " << SQUARE(5) << std::endl;
    std::cout << "Max of 10 and 20 = " << MAX(10, 20) << std::endl;

    // 使用多行宏
    PRINT_INFO("John", 25);

    // 条件编译示例
    #if DEBUG
        std::cout << "Debug mode is on" << std::endl;
    #else
        std::cout << "Debug mode is off" << std::endl;
    #endif

    return 0;
} 