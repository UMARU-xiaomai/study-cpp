#include <iostream>
#include <string>

// 模板函数示例
template<typename T>
void printType(T value) {
    std::cout << "通用模板: " << value << std::endl;
}

// 全特化版本 - 针对const char*
template<>
void printType<const char*>(const char* value) {
    std::cout << "全特化(const char*): " << value << std::endl;
}

// 偏特化版本 - 针对指针类型
template<typename T>
void printType(T* value) {
    std::cout << "偏特化(指针类型): " << *value << std::endl;
}

// 模板类示例
template<typename T1, typename T2>
class Pair {
public:
    Pair(T1 first, T2 second) : first(first), second(second) {}
    
    void print() {
        std::cout << "通用模板: " << first << ", " << second << std::endl;
    }
    
private:
    T1 first;
    T2 second;
};

// 全特化版本 - 针对int, int
template<>
class Pair<int, int> {
public:
    Pair(int first, int second) : first(first), second(second) {}
    
    void print() {
        std::cout << "全特化(int,int): " << first << " + " << second 
                 << " = " << first + second << std::endl;
    }
    
private:
    int first;
    int second;
};

// 偏特化版本 - 第二个类型与第一个相同
template<typename T>
class Pair<T, T> {
public:
    Pair(T first, T second) : first(first), second(second) {}
    
    void print() {
        std::cout << "偏特化(相同类型): " << first << " and " << second << std::endl;
    }
    
private:
    T first;
    T second;
};

int main() {
    std::cout << "=== 模板函数特例化示例 ===" << std::endl;
    printType(10);              // 通用模板
    printType("Hello");         // 全特化(const char*)
    
    int x = 20;
    printType(&x);              // 偏特化(指针类型)
    
    std::cout << "\n=== 模板类特例化示例 ===" << std::endl;
    Pair<double, std::string> p1(3.14, "pi");
    p1.print();                 // 通用模板
    
    Pair<int, int> p2(10, 20);
    p2.print();                 // 全特化(int,int)
    
    Pair<std::string, std::string> p3("Hello", "World");
    p3.print();                 // 偏特化(相同类型)
    
    return 0;
}