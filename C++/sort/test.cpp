#include "sort.h"
#include<iostream>
using namespace std;
void PrintSort(int*a,int n)
{
	for(int i = 0; i < n; ++i)
	{
	  std::cout << a[i] << " ";
	}
  std::cout << std::endl;
}
void TestSort()
{
	int a[] = {3,6,1,4,5,2,7,9,8};
	int n = sizeof(a)/sizeof(a[0]);
	//Insertsort(a,n);
	//SelectSort(a,n);
	//ShellSort(a,n);
	//HeapSort(a,n);
	//BubbleSort(a,n);
	QuickSort(a,0,n-1);
	PrintSort(a,n);
}
int main()
{
	TestSort();
	//Test1();
	return 0;
}
