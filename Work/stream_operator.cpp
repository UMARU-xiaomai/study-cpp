#include <bits/stdc++.h>
using namespace std;

class A
{
private:
    int x;
    string name;
    
public:
    A(int x = 0, string name = "默认") : x(x), name(name) {}
    
    // 声明友元函数重载输出流运算符
    friend ostream& operator<<(ostream& os, const A& obj);
    
    // 声明友元函数重载输入流运算符
    friend istream& operator>>(istream& is, A& obj);
};

// 实现输出流运算符重载
ostream& operator<<(ostream& os, const A& obj)
{
    os << "A对象: [x=" << obj.x << ", name=" << obj.name << "]";
    return os;
}

// 实现输入流运算符重载
istream& operator>>(istream& is, A& obj)
{
    cout << "请输入x值: ";
    is >> obj.x;
    cout << "请输入name值: ";
    is >> obj.name;
    return is;
}

int main()
{
    // 创建A类对象
    A a1(10, "测试对象");
    
    // 使用重载的输出流运算符
    cout << "输出a1: " << a1 << endl;
    
    // 创建新对象并使用重载的输入流运算符
    A a2;
    cout << "请为a2输入数据:" << endl;
    cin >> a2;
    
    // 输出a2验证输入
    cout << "输出a2: " << a2 << endl;
    
    return 0;
}