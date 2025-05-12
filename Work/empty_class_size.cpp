#include <iostream>

// 定义一个空类
class EmptyClass {
    // 不包含任何成员变量和成员函数
};

// 定义一个包含虚函数的空类
class EmptyClassWithVirtual {
public:
    virtual void doNothing() {}
};

// 定义一个从空类继承的类
class DerivedFromEmpty : public EmptyClass {
    char x;  // 添加一个字节的成员变量
};

int main() {
    std::cout << "=== 空类大小测试 ===" << std::endl;

    // 测试空类的大小
    std::cout << "空类(EmptyClass)的大小: " << sizeof(EmptyClass) 
              << " 字节" << std::endl;
    // 解释：C++标准要求即使是空类也必须占用至少1字节的空间，
    // 这是为了确保类的不同实例在内存中具有不同的地址

    // 测试空类数组
    EmptyClass arr[10];
    std::cout << "空类数组的大小: " << sizeof(arr)
              << " 字节 (10个实例 * 1字节)" << std::endl;

    // 测试带有虚函数的空类大小
    std::cout << "带虚函数的空类大小: " << sizeof(EmptyClassWithVirtual)
              << " 字节 (包含虚函数表指针)" << std::endl;

    // 测试从空类继承的类的大小
    std::cout << "从空类继承的类大小: " << sizeof(DerivedFromEmpty)
              << " 字节 (1字节成员变量)" << std::endl;

    return 0;
}