#include <iostream>
#include <string>

// 基类
class Animal {
protected:
    std::string name;
public:
    Animal(const std::string& n) : name(n) {
        std::cout << "Animal constructor called for " << name << std::endl;
    }
    virtual ~Animal() {
        std::cout << "Animal destructor called for " << name << std::endl;
    }
    virtual void makeSound() = 0;
};

// 使用虚继承
class Mammal : virtual public Animal {
public:
    Mammal(const std::string& n) : Animal(n) {
        std::cout << "Mammal constructor called for " << name << std::endl;
    }
    virtual ~Mammal() {
        std::cout << "Mammal destructor called for " << name << std::endl;
    }
};

// 使用虚继承
class Bird : virtual public Animal {
public:
    Bird(const std::string& n) : Animal(n) {
        std::cout << "Bird constructor called for " << name << std::endl;
    }
    virtual ~Bird() {
        std::cout << "Bird destructor called for " << name << std::endl;
    }
};

// 最终派生类
class Bat : public Mammal, public Bird {
public:
    Bat(const std::string& n) : Animal(n), Mammal(n), Bird(n) {
        std::cout << "Bat constructor called for " << name << std::endl;
    }
    ~Bat() override {
        std::cout << "Bat destructor called for " << name << std::endl;
    }
    void makeSound() override {
        std::cout << name << " makes a high-pitched squeak!" << std::endl;
    }
};

int main() {
    Bat bat("Bruce");
    bat.makeSound();
    return 0;
} 