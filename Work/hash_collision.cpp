#include <iostream>
#include <vector>
#include <list>
#include <string>

// 1. 开放寻址法（线性探测）
class LinearProbingHash {
private:
    static const int TABLE_SIZE = 10;
    std::vector<std::pair<int, std::string>> table;
    std::vector<bool> isOccupied;

public:
    LinearProbingHash() : table(TABLE_SIZE), isOccupied(TABLE_SIZE, false) {}

    int hash(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key, const std::string& value) {
        int index = hash(key);
        int originalIndex = index;
        
        do {
            if (!isOccupied[index]) {
                table[index] = std::make_pair(key, value);
                isOccupied[index] = true;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (index != originalIndex);
        
        std::cout << "哈希表已满！" << std::endl;
    }

    std::string search(int key) {
        int index = hash(key);
        int originalIndex = index;
        
        do {
            if (isOccupied[index] && table[index].first == key) {
                return table[index].second;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (index != originalIndex);
        
        return "未找到";
    }
};

// 2. 链地址法（拉链法）
class ChainingHash {
private:
    static const int TABLE_SIZE = 10;
    std::vector<std::list<std::pair<int, std::string>>> table;

public:
    ChainingHash() : table(TABLE_SIZE) {}

    int hash(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key, const std::string& value) {
        int index = hash(key);
        table[index].push_back(std::make_pair(key, value));
    }

    std::string search(int key) {
        int index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return "未找到";
    }
};

// 3. 再哈希法
class DoubleHashingHash {
private:
    static const int TABLE_SIZE = 10;
    std::vector<std::pair<int, std::string>> table;
    std::vector<bool> isOccupied;

public:
    DoubleHashingHash() : table(TABLE_SIZE), isOccupied(TABLE_SIZE, false) {}

    int hash1(int key) {
        return key % TABLE_SIZE;
    }

    int hash2(int key) {
        return 7 - (key % 7);  // 使用一个不同的质数
    }

    void insert(int key, const std::string& value) {
        int index = hash1(key);
        int step = hash2(key);
        int originalIndex = index;
        
        do {
            if (!isOccupied[index]) {
                table[index] = std::make_pair(key, value);
                isOccupied[index] = true;
                return;
            }
            index = (index + step) % TABLE_SIZE;
        } while (index != originalIndex);
        
        std::cout << "哈希表已满！" << std::endl;
    }

    std::string search(int key) {
        int index = hash1(key);
        int step = hash2(key);
        int originalIndex = index;
        
        do {
            if (isOccupied[index] && table[index].first == key) {
                return table[index].second;
            }
            index = (index + step) % TABLE_SIZE;
        } while (index != originalIndex);
        
        return "未找到";
    }
};

int main() {
    std::cout << "=== 哈希冲突解决方案示例 ===" << std::endl;

    // 1. 测试线性探测
    std::cout << "\n1. 线性探测法测试：" << std::endl;
    LinearProbingHash linearHash;
    linearHash.insert(1, "一");
    linearHash.insert(11, "十一");  // 会发生冲突
    std::cout << "查找 1: " << linearHash.search(1) << std::endl;
    std::cout << "查找 11: " << linearHash.search(11) << std::endl;

    // 2. 测试链地址法
    std::cout << "\n2. 链地址法测试：" << std::endl;
    ChainingHash chainHash;
    chainHash.insert(1, "一");
    chainHash.insert(11, "十一");  // 会发生冲突
    std::cout << "查找 1: " << chainHash.search(1) << std::endl;
    std::cout << "查找 11: " << chainHash.search(11) << std::endl;

    // 3. 测试再哈希法
    std::cout << "\n3. 再哈希法测试：" << std::endl;
    DoubleHashingHash doubleHash;
    doubleHash.insert(1, "一");
    doubleHash.insert(11, "十一");  // 会发生冲突
    std::cout << "查找 1: " << doubleHash.search(1) << std::endl;
    std::cout << "查找 11: " << doubleHash.search(11) << std::endl;

    return 0;
} 