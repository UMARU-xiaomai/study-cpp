#include <iostream>
#include <memory>
#include <string>

// 示例类
class Resource {
public:
    Resource(const std::string& name) : name_(name) {
        std::cout << "Resource " << name_ << " created" << std::endl;
    }
    
    ~Resource() {
        std::cout << "Resource " << name_ << " destroyed" << std::endl;
    }
    
    void use() {
        std::cout << "Using resource: " << name_ << std::endl;
    }
    
private:
    std::string name_;
};

// 1. unique_ptr 示例
/*
unique_ptr 特点：
1. 独占所有权：同一时间只能有一个 unique_ptr 指向特定对象
2. 不能复制，只能移动（std::move）
3. 当 unique_ptr 被销毁时，它所指向的对象也会被自动销毁
4. 没有额外的开销，性能接近原始指针
5. 推荐使用 make_unique 创建（C++14）
*/
void unique_ptr_example() {
    std::cout << "\n=== unique_ptr Example ===" << std::endl;
    
    // 创建 unique_ptr
    std::unique_ptr<Resource> ptr1(new Resource("Unique1"));
    // 或使用 make_unique (C++14)
    auto ptr3 = std::make_unique<Resource>("Unique2");
    ptr3->use();

    // 使用 -> 操作符访问成员
    // ##关键##
    ptr1->use();
    (*ptr1).use();
    
    // 移动语义：由于 unique_ptr 独占所有权，所以不能直接赋值，需要使用 std::move 进行移动
    // ##关键##
    std::unique_ptr<Resource> ptr2 = std::move(ptr1);
    // 通过move的含义理解：
    // move是将左值转换为右值，从而进行移动而不是拷贝
    // 移动后，原对象的指针将被设置为nullptr
    // 而内容物移到ptr2中
    
    // 此时 ptr1 为 nullptr
    if (!ptr1) {
        std::cout << "ptr1 is now nullptr" << std::endl;
    }

    // 释放所有权
    // 方法1：使用 reset() 显式释放
    ptr2.reset();
    // 方法2：将指针设置为 nullptr
    ptr2 = nullptr;
    // 注：其它智能指针释放方式类似
}

// 2. shared_ptr 示例
/*
shared_ptr 特点：
1. 共享所有权：多个 shared_ptr 可以指向同一个对象
2. 使用引用计数机制
3. 当最后一个指向对象的 shared_ptr 被销毁时，对象才会被销毁
4. 支持复制和移动操作
5. 推荐使用 make_shared 创建（性能更好）
6. 可能存在循环引用问题
*/
void shared_ptr_example() {
    std::cout << "\n=== shared_ptr Example ===" << std::endl;
    
    // 创建 shared_ptr
    std::shared_ptr<Resource> ptr1(new Resource("Shared1"));
    // 或使用 make_shared (C++14)
    auto ptr3 = std::make_shared<Resource>("Shared2");
    
    // 引用计数为1
    std::cout << "Reference count: " << ptr1.use_count() << std::endl;
    
    // 创建另一个 shared_ptr 指向同一个对象
    std::shared_ptr<Resource> ptr2 = ptr1;
    
    // 引用计数为2
    std::cout << "Reference count: " << ptr1.use_count() << std::endl;
    
    // 使用资源
    ptr1->use();
    ptr2->use();

    // 释放所有权
    ptr1.reset();
    ptr2.reset();
}

// 3. weak_ptr 示例
/*
weak_ptr 特点：
1. 弱引用：不增加引用计数
2. 不能直接访问对象，必须转换为 shared_ptr
3. 用于解决 shared_ptr 的循环引用问题
4. 通过 lock() 方法检查对象是否还存在
5. 不会影响对象的生命周期
*/
void weak_ptr_example() {
    std::cout << "\n=== weak_ptr Example ===" << std::endl;
    
    // 创建 shared_ptr
    std::shared_ptr<Resource> shared = std::make_shared<Resource>("SharedForWeak");
    
    // 创建 weak_ptr
    std::weak_ptr<Resource> weak = shared;
    
    // 检查资源是否还存在
    // ##关键##
    // 如果资源存在，则lock() 返回一个 shared_ptr 指向该资源
    // 如果资源不存在，则lock() 返回一个空的 shared_ptr
    if (auto resource = weak.lock()) {
        std::cout << "Resource is still alive" << std::endl;
        resource->use();
        // 重置weak_ptr，避免循环引用
        // 注意不是unlock()
        resource.reset();
    }
    // 当通过 weak_ptr::lock() 获得的临时 shared_ptr 离开作用域时，引用计数会减1。这是因为：
    // lock() 返回的是一个新的 shared_ptr 对象
    // 这个 shared_ptr 对象遵循正常的 RAII 原则
    // 当它离开作用域时，会自动调用析构函数，从而减少引用计数

    // 重置 shared_ptr
    shared.reset();
    
    // 再次检查
    if (auto resource = weak.lock()) {
        std::cout << "This won't be printed" << std::endl;
    } else {
        std::cout << "Resource has been destroyed" << std::endl;
    }
}

// 4. auto_ptr 示例 (已废弃，仅作演示)
/*
auto_ptr 特点（已废弃）：
1. C++98 引入，C++17 中已被移除
2. 存在所有权转移的隐式语义，容易导致意外行为
3. 不支持数组
4. 不能用于 STL 容器
5. 建议使用 unique_ptr 替代
*/
void auto_ptr_example() {
    std::cout << "\n=== auto_ptr Example (Deprecated) ===" << std::endl;
    
    // 注意：auto_ptr 在 C++17 中已被移除
    // 这里仅作演示，实际开发中应使用 unique_ptr
    std::auto_ptr<Resource> ptr(new Resource("Auto"));
    ptr->use();
}

int main() {
    unique_ptr_example();
    shared_ptr_example();
    weak_ptr_example();
    auto_ptr_example();
    
    return 0;
}
