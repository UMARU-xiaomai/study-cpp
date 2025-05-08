#include <iostream>

// 使用 #pragma pack 可以改变默认的对齐方式
#pragma pack(1)  // 设置为1字节对齐
struct PackedStruct {
    char c;      // 1字节
    int i;       // 4字节
    double d;    // 8字节
};
#pragma pack()   // 恢复默认对齐

// 默认对齐的结构体
struct DefaultStruct {
    char c;      // 1字节
    int i;       // 4字节
    double d;    // 8字节
};

int main() {
    std::cout << "=== 结构体内存对齐示例 ===" << std::endl;
    
    // 打印各个成员的大小
    std::cout << "char 大小: " << sizeof(char) << " 字节" << std::endl;
    std::cout << "int 大小: " << sizeof(int) << " 字节" << std::endl;
    std::cout << "double 大小: " << sizeof(double) << " 字节" << std::endl;
    
    // 打印结构体大小
    std::cout << "\nPackedStruct 大小: " << sizeof(PackedStruct) << " 字节" << std::endl;
    std::cout << "DefaultStruct 大小: " << sizeof(DefaultStruct) << " 字节" << std::endl;

    // 打印成员偏移量
    std::cout << "\nPackedStruct 成员偏移量：" << std::endl;
    std::cout << "c 偏移量: " << offsetof(PackedStruct, c) << std::endl;
    std::cout << "i 偏移量: " << offsetof(PackedStruct, i) << std::endl;
    std::cout << "d 偏移量: " << offsetof(PackedStruct, d) << std::endl;

    std::cout << "\nDefaultStruct 成员偏移量：" << std::endl;
    std::cout << "c 偏移量: " << offsetof(DefaultStruct, c) << std::endl;
    std::cout << "i 偏移量: " << offsetof(DefaultStruct, i) << std::endl;
    std::cout << "d 偏移量: " << offsetof(DefaultStruct, d) << std::endl;

    return 0;
} 