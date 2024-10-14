#include <bits/stdc++.h>
using namespace std;


	/**
	# 迭代器
	## 基本设计概念
	对于一个类，想要遍历其可遍历属性时可利用此模式。
	在类中定义一个新的iterator类，全面接管for循环的三个语句（起始/终止条件/下一项）
	## 官方的iterator类
	### 迭代器主要分为以下几类：

	- 输入迭代器（Input Iterator）：只能进行单次读取操作，不能进行写入操作。
	- 输出迭代器（Output Iterator）：只能进行单次写入操作，不能进行读取操作。
	- 正向迭代器（Forward Iterator）：可以进行读取和写入操作，并且可以向前移动。
	- 双向迭代器（Bidirectional Iterator）：除了可以进行正向迭代器的所有操作外，还可以向后移动。
	- 随机访问迭代器（Random Access Iterator）：除了可以进行双向迭代器的所有操作外，还可以进行随机访问，例如通过下标访问元素。
	
	### 使用迭代器遍历容器
	for (ContainerType::iterator it = container.begin(); it != container.end(); ++it) {
    // 访问元素: *it
	}
	
	##设计
	
	**/

class Group
{
	int arr[40];
public:
	Group(){
		for(int i =0 ;i<40;i++)
		{
			arr[i] = i+1;
		}
	}
	
	
	~Group() = default;
	class Iterator
	{
		int* i_ptr;
		
	public:
		Iterator(int* start_i):i_ptr(start_i){}
		
		bool operator!=(const Iterator &b){ return i_ptr != b.i_ptr;}
		Iterator &operator++() { i_ptr++; return *this;}
		
		int &operator*() const { return *i_ptr; }
	};
	
	//
	Iterator begin() { return Iterator(&(arr[0])); }
	Iterator end() { return Iterator(&(arr[40])); }
};


int main()
{
	Group gp;
	
	for(Group::Iterator it = gp.begin();it!=gp.end();++it)
	{
		cout<<*it<<endl;
	}
}