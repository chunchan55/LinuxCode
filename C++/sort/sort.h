#include <iostream>
using namespace std;
#include<assert.h>

//1.��������
//��������
//ʱ�临�Ӷȣ�O(N^2) �ռ临�Ӷ�O(1)û���ռ䣬������һ����ʱ����tmp  �ȶ�
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
				--end;//�����1��Ϊ�˺����end+1��ֵ��Ҳ����ǰһ��ֵ��
			}
			else
			{
				break;
			}
		}
		a[end+1] = tmp;//ÿ�ζ��ǰ�ֵ��end+1 ���λ��
	}

}
//ϣ�����򣬸о��Ͳ����������� ƽ��O(N^1.2)  �O(N^2)���ȶ�
void ShellSort(int*a,int n)
{
	assert(a);
	int gap = n;
	while(gap > 1)
	{
		gap = gap/3 + 1;
		if(gap < 3)
		{
			Insertsort(a,n);//������پ�ֱ���ò�������ͺã�
		}
		for(int i = 0; i < n - gap; ++i)
		{
			//����ľ����Ʋ�������
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


//2,ѡ������
//��1��ֱ��ѡ������ ʱ�临�Ӷ�O(N^2) ���ȶ�
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

//��2��������  O(nlogn)
void AdjustDown(int*a,size_t root,size_t n)
{
	assert(a);
	size_t parent = root;
	size_t child = parent*2 + 1;
	while(child < n)
	{
		//�ҵ����ĺ��� 
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
	for(int i = (n-2)/2; i >=0; --i)//������int  Ҫ��Ȼi = 0 ʱ -1 �ͱ�Ϊ4290000000��
	{
		//����
		AdjustDown(arr,i,n);
	}
	for(int i = n-1; i >= 1; --i)
	{
		swap(arr[0],arr[i]);//ͷβ����
		AdjustDown(arr,0,i);//����,
	}

}

//3.��������
//(1)ð������
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
		if(stat == false)//˵����û����
		{
			break;
		}
	}
}

////��2����������
int GetMidIndex(int*a,int left,int right)//����ȡ���Ż�
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
//����ָ�뷨

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
	//��߱�keyС�ұ߱�key��
}
//����
int PartSort2(int*a,int left,int right)
{
	//��prev��ߵĶ��Ǳ�a[right]С�ģ��ұߵĶ��Ǳ������
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

//�鲢����

