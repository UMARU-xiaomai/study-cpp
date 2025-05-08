#include <iostream>

// 基类
class Base {
public:
    virtual void print() {
        std::cout << "Base class" << std::endl;
    }
    virtual ~Base() {}
};

// 派生类
class Derived : public Base {
public:
    void print() override {
        std::cout << "Derived class" << std::endl;
    }
};

int main() {
    // 1. static_cast 示例
    std::cout << "=== static_cast 示例 ===" << std::endl;
    double d = 3.14;
    int i = static_cast<int>(d);  // 浮点数转整数
    std::cout << "double: " << d << " -> int: " << i << std::endl;

    // 2. dynamic_cast 示例
    std::cout << "\n=== dynamic_cast 示例 ===" << std::endl;
    Base* base = new Derived();
    Derived* derived = dynamic_cast<Derived*>(base);
    if (derived) {
        std::cout << "转换成功！" << std::endl;
        derived->print();
    }

    // 3. const_cast 示例
    std::cout << "\n=== const_cast 示例 ===" << std::endl;
    const int const_num = 10;
    int& num_ref = const_cast<int&>(const_num);
    num_ref = 20;
    std::cout << "修改后的值: " << const_num << std::endl;

    // 4. reinterpret_cast 示例
    std::cout << "\n=== reinterpret_cast 示例 ===" << std::endl;
    int* ptr = new int(42);
    long long addr = reinterpret_cast<long long>(ptr);
    std::cout << "指针地址: " << addr << std::endl;

    // 清理内存
    delete base;
    delete ptr;

    return 0;
} 