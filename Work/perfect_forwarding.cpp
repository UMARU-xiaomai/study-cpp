#include <iostream>
#include <string>
#include <utility>

// 用于演示的类
class MyClass {
public:
    MyClass() { std::cout << "默认构造函数" << std::endl; }
    MyClass(const MyClass&) { std::cout << "拷贝构造函数" << std::endl; }
    MyClass(MyClass&&) { std::cout << "移动构造函数" << std::endl; }
    
    // 用于演示的成员函数
    void process(const std::string& s) {
        std::cout << "处理左值: " << s << std::endl;
    }
    
    void process(std::string&& s) {
        std::cout << "处理右值: " << s << std::endl;
    }
};

// 不使用完美转发的包装函数
template<typename T>
void wrapperWithoutForwarding(T param) {
    std::cout << "\n不使用完美转发：" << std::endl;
    MyClass obj;
    obj.process(param);  // 参数总是作为左值传递
}

// 使用完美转发的包装函数
template<typename T>
void wrapperWithForwarding(T&& param) {
    std::cout << "\n使用完美转发：" << std::endl;
    MyClass obj;
    obj.process(std::forward<T>(param));  // 保持参数的值类别
}

// 演示多个参数的完美转发
template<typename T1, typename T2>
void multiParamWrapper(T1&& param1, T2&& param2) {
    std::cout << "\n多参数完美转发：" << std::endl;
    MyClass obj;
    obj.process(std::forward<T1>(param1));
    obj.process(std::forward<T2>(param2));
}

int main() {
    std::cout << "=== 完美转发示例 ===" << std::endl;

    // 测试左值
    std::string lvalue = "左值字符串";
    std::cout << "\n测试左值：" << std::endl;
    wrapperWithoutForwarding(lvalue);
    wrapperWithForwarding(lvalue);

    // 测试右值
    std::cout << "\n测试右值：" << std::endl;
    wrapperWithoutForwarding(std::string("右值字符串"));
    wrapperWithForwarding(std::string("右值字符串"));

    // 测试多参数
    std::cout << "\n测试多参数：" << std::endl;
    std::string str1 = "第一个参数";
    multiParamWrapper(str1, std::string("第二个参数"));

    // 测试 const 左值
    const std::string constLvalue = "const左值字符串";
    std::cout << "\n测试const左值：" << std::endl;
    wrapperWithForwarding(constLvalue);

    return 0;
} 