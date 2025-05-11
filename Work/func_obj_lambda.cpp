#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Compare {
    bool operator()(int a, int b) const {
        return a < b;
    }
};

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5};
    int target = 3;
    // 两种自定义排序方式：
    // lambda
    sort(numbers.begin(), numbers.end(), [](int a, int b) -> bool {
        return a < b;
    });
    // 函数对象 / function object
    sort(numbers.begin(), numbers.end(), Compare());

}