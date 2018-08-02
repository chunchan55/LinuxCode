#include <iostream>
using namespace std;
#include<assert.h>

//1.插入排序
//插入排序
//时间复杂度：O(N^2) 空间复杂度O(1)没开空间，就用了一个临时变量tmp  稳定
void Insertsort(int *a,size_t n)
{
	assert(a);
	for(size_t i=0;i<n-1;++i)
	{
		int tmp = 0;
		int end = i;
		tmp = a[end+1];
		while(end>=0)
		{
			if(tmp<a[end])
			{
				a[end+1] = a[end];
				--end;//这里减1，为了后面给end+1赋值（也就是前一个值）
			}
			else
			{
				break;
			}
		}
		a[end+1] = tmp;//每次都是把值给end+1 这个位置
	}

}
//希尔排序，感觉和插入排序类似 平均O(N^1.2)  最坏O(N^2)不稳定
void ShellSort(int*a,int n)
{
	assert(a);
	int gap = n;
	while(gap > 1)
	{
		gap = gap/3 + 1;
		if(gap < 3)
		{
			Insertsort(a,n);//如果很少就直接用插入排序就好，
		}
		for(int i = 0; i < n - gap; ++i)
		{
			//下面的就类似插入排序
			int end = i;
			int tmp = a[end+gap];
			while(end >= 0)
			{
				if(a[end] > tmp)
				{
					a[end+gap] = a[end];
					end -= gap;
				}
				else
					break;
			}
			a[end+gap] = tmp;
		}
	}
}


//2,选择排序
//（1）直接选择排序 时间复杂度O(N^2) 不稳定
void SelectSort(int* a,int n)
{
	assert(a);
	int min = 0;
	int tmp = 0;
	for(int i = 0; i < n; ++i)
	{
		min = i;
		for(int j = i + 1; j < n; ++j)
		{
			if(a[min] > a[j])
			{
				min = j;
			}
		}
		if(min != i)
		{
			tmp = a[min];
			a[min] = a[i];
			a[i] = tmp;
		}
	}
}

//（2）堆排序  O(nlogn)
void AdjustDown(int*a,size_t root,size_t n)
{
	assert(a);
	size_t parent = root;
	size_t child = parent*2 + 1;
	while(child < n)
	{
		//找到最大的孩子 
		if(child+1 < n && a[child+1] > a[child])
			++child;
		if(a[child] > a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = parent*2 + 1;
		}
		else
			break;
	}
}
void HeapSort(int*arr,size_t n)
{
	assert(arr);
	for(int i = (n-2)/2; i >=0; --i)//这里用int  要不然i = 0 时 -1 就变为4290000000了
	{
		//建堆
		AdjustDown(arr,i,n);
	}
	for(int i = n-1; i >= 1; --i)
	{
		swap(arr[0],arr[i]);//头尾交换
		AdjustDown(arr,0,i);//排序,
	}

}

//3.交换排序
//(1)冒泡排序
void BubbleSort(int*arr,size_t n)
{
	//assert(arr);
	bool stat = false;
	for(size_t i = 0; i < n; ++i)
	{
		for(size_t j = 0; j < n-1; ++j)
		{
			if(arr[j] > arr[j+1])
			{
				swap(arr[j],arr[j+1]);
				stat = true;
			}
		}
		if(stat == false)//说明就没交换
		{
			break;
		}
	}
}

////（2）快速排序
int GetMidIndex(int*a,int left,int right)//三数取中优化
{
	int mid = left+(right-left)/2;
	if(a[left]<a[mid])
	{
		if(a[mid]<a[right])
		{
			return mid;
		}
		else if(a[left]>a[right])
		{
			return left;
		}		
	}
	else 
	{
		if(a[left]<a[right])
		{
			return left;
		}
		if(a[right]<a[mid])
		{
			return mid;
		}	
	}
	return right;
}
//左右指针法

int PartSort(int*a,int left,int right)
{
	assert(a);
	int mid = GetMidIndex(a,left,right);
	swap(a[mid],a[right]);
	int &key = a[right];
	int begin = left;
	int end = right;
	while(begin < end)
	{
		while(begin<end &&a[begin] <= key)
		{
			++begin;
		}
		while(begin<end && a[end] >= key)
		{
			--end;
		}
		if(begin < end)
		{
			swap(a[begin],a[end]);
		}
	}
	swap(a[begin],key);
	return begin;
	//左边比key小右边比key大
}
//链表法
int PartSort2(int*a,int left,int right)
{
	//在prev左边的都是比a[right]小的，右边的都是比他大的
	assert(a);
	int prev = left-1;
	int cur = left;
	while(cur < right)
	{
		if(a[cur] < a[right] && prev++!=cur)
		{
			swap(a[prev],a[cur]);
		}
		++cur;
	}
	swap(a[++prev],a[right]);
	return prev;
}
void QuickSort(int*a,int left,int right)
{
	assert(a);
	if(left >= right)
		return;
	int div = PartSort2(a,left,right);
	QuickSort(a,left,div-1);
	QuickSort(a,div+1,right);
}

//归并排序

