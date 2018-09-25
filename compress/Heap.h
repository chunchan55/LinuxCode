#pragma once
#include <iostream>
#include <vector>
using namespace std;

//仿函数，思想，重载operator()，不管是大堆还是小堆都不用管，直接用就可以
template<class T>
struct Greater
{
	bool operator()(T&h1,T&h2)
	{
		return h1>h2;
	}
};
template<class T>
struct Less
{
	bool operator()(T&h1,T&h2)
	{
		return h1<h2;
	}
};
template<class T,class Compare>
class Heap
{
private:
	vector<T> _hp;
public:
	Heap()//这里写一个默认的
	{}
	Heap(T*a,size_t n)//建大堆
	{
		_hp.reserve(n);
		for(size_t i=0;i<n;++i)
		{
			_hp.push_back(a[i]);
		}
		for(int i=(_hp.size()-2)/2;i>=0;--i)
		{
			//注意参数类型，用int。要不然用size_t条件就永远成立，就会死循环
			AdjustDown(i);
		}
	}
	void Push(const T&h)
	{
		_hp.push_back(h);//插入后还要调整
		AdjustUp(_hp.size()-1);//向上调整
	}
	void Pop()//头删
	{
		assert(!_hp.empty());
		swap(_hp[0],_hp[_hp.size()-1]);//头尾交换，用顺序表的尾删，在调整堆
		_hp.pop_back();
		AdjustDown(0);//向下调整
	}
	void Print()
	{
		for(size_t i=0;i<Size();++i)
		{
			cout<<_hp[i]<<" ";
		}
		cout<<endl;
	}
	size_t Size()
	{
		return _hp.size();
	}
	T& Top()
	{
		assert(!_hp.empty());
		return _hp[0];
	}
	T& Last()
	{
		assert(!_hp.empty());
		return _hp[_hp.size()-1];
	} 
private:
	void AdjustDown(size_t root)//向上调整
	{
		Compare com;
		size_t parent = root;
		size_t child = parent*2+1;
		while(child<_hp.size())//判断下标是否合法
		{
			if(child+1<_hp.size()&&com(_hp[child+1],_hp[child]))//判断下表是否合法，并找到最大的那个孩子
			{
				++child;
			}
			//到这里,_hp[child]一定是最大的
			if(com(_hp[child],_hp[parent]))
			{
				swap(_hp[child],_hp[parent]);
				parent = child;
				child = parent*2-1;
			}
			else
			{
				break;
			}
		}
	}
void AdjustUp(size_t root)
{
	Compare com;
	size_t child = root;
	size_t parent = (child-1)/2;
	while(child>0)
	{
		if(com(_hp[child],_hp[parent]))
		{
			swap(_hp[child],_hp[parent]);
			child = parent;
			parent = (child-1)/2;
		}
		else 
			break;
	}
}

};

void HeapTest()
{
	int a[] = {10,11,13,12,16,18,15,17,14,19};
	int ret = sizeof(a)/sizeof(a[0]);
	Heap<int,Greater<int>> h1(a,ret);
	h1.Print();
	Heap<int,Less<int>> h2(a,ret);
	h2.Print();	
}