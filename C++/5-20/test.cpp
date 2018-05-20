#include<iostream>
using namespace std;
#include<stdlib.h>
int SumMax(int*arr,int n)
{
	int max = 0;
	int sum = 0;
	for(int i = 0; i < n; ++i)
	{
		for(int j = i; j < n; j++)
		{
			for(int k = i; k <= j; ++k)
			{
				sum += arr[k];
			}
			if(sum > max)
			{
				max = sum;
			}
			sum = 0;
		}
	}
	return  max;
}

int main()
{
	int n = 0;
	cin >> n;
	int *arr = (int*)malloc(n*sizeof(int));
	for(int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	int maxsum = SumMax(arr,n);
	cout <<maxsum << endl;
}
