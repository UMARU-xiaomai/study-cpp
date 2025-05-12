#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>

// 演示5种迭代器类型
void demoIterators() {
    // 1. 输入迭代器
    std::cout << "=== 输入迭代器示例 ===" << std::endl;
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::istream_iterator<int> input_it(std::cin);
    std::cout << "输入迭代器读取的值: " << *input_it << std::endl;

    // 2. 输出迭代器
    std::cout << "\n=== 输出迭代器示例 ===" << std::endl;
    std::ostream_iterator<int> output_it(std::cout, " ");
    *output_it = 10;
    ++output_it;
    *output_it = 20;
    std::cout << std::endl;

    // 3. 前向迭代器
    std::cout << "\n=== 前向迭代器示例 ===" << std::endl;
    std::list<int> lst{1, 2, 3, 4, 5};
    auto forward_it = lst.begin();
    std::cout << "前向迭代器遍历list: ";
    while(forward_it != lst.end()) {
        std::cout << *forward_it << " ";
        ++forward_it;
    }
    std::cout << std::endl;

    // 4. 双向迭代器
    std::cout << "\n=== 双向迭代器示例 ===" << std::endl;
    auto bi_it = lst.end();
    std::cout << "双向迭代器反向遍历list: ";
    while(bi_it != lst.begin()) {
        --bi_it;
        std::cout << *bi_it << " ";
    }
    std::cout << std::endl;

    // 5. 随机访问迭代器
    std::cout << "\n=== 随机访问迭代器示例 ===" << std::endl;
    auto random_it = vec.begin();
    std::cout << "随机访问迭代器直接访问第3个元素: " << random_it[2] << std::endl;
    std::cout << "迭代器算术运算(第3个元素+2): " << *(random_it + 4) << std::endl;
}

int main() {
    demoIterators();
    return 0;
}