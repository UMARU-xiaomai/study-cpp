#include <iostream>
#include <typeinfo>

// 基类
class Animal {
public:
    virtual void makeSound() = 0;  // 纯虚函数
    virtual ~Animal() {}  // 虚析构函数
};

// 派生类
class Dog : public Animal {
public:
    void makeSound() override {
        std::cout << "Woof!" << std::endl;
    }
    
    void wagTail() {
        std::cout << "Dog is wagging its tail" << std::endl;
    }
};

// 另一个派生类
class Cat : public Animal {
public:
    void makeSound() override {
        std::cout << "Meow!" << std::endl;
    }
    
    void purr() {
        std::cout << "Cat is purring" << std::endl;
    }
};

int main() {
    // 创建对象
    Animal* animals[] = {new Dog(), new Cat()};
    
    // 使用 typeid 进行类型检查
    for (Animal* animal : animals) {
        std::cout << "Type: " << typeid(*animal).name() << std::endl;
        
        // 使用 dynamic_cast 进行安全的类型转换
        if (Dog* dog = dynamic_cast<Dog*>(animal)) {
            std::cout << "This is a Dog!" << std::endl;
            dog->wagTail();
        }
        else if (Cat* cat = dynamic_cast<Cat*>(animal)) {
            std::cout << "This is a Cat!" << std::endl;
            cat->purr();
        }
        
        animal->makeSound();
        std::cout << "------------------------" << std::endl;
    }
    
    // 清理内存
    for (Animal* animal : animals) {
        delete animal;
    }
    
    return 0;
} 