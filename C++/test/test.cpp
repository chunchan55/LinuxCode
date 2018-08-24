#include<iostream>
using namespace std;
#include<string.h>
#include<string>
int Find(string str)
{
	int len = str.size();
	int hashtable[1024] = {0};
	for(int i = 0; i<len; ++i)
	{
		hashtable[str[i]]++;
	}
	for(int j = 0; j<len; j++)
	{
		if(hashtable[str[j]] == 1)
		{
			return j;
		}
	}
	return -1;
}
int main()
{
	string s;
	cin >> s;
	int tmp = Find(s);
	if(tmp == -1 )
		cout << "-1\n";
	else
		cout << s[tmp]<< endl;
	return 0;
}
//相邻两个小朋友，成绩较高的比较低的多一个贴纸
//int main()
//{
//  int tmp[5];
//  for(int i = 0; i< 5; i++)
//  {
//    cin >>  tmp[i];
//  }
//  int num = 0;
//  int i = 1;
//  int ppre = 1;
//  int pre = 1;
//  for(i = 1; i<5; i+=2)
//  {
//    int cur = 1;
//    if(tmp[i-1] > tmp[i])
//    {
//      if(ppre >1)
//        pre = 1;
//      if(i+1 < 5 && tmp[i]>tmp[i+1])
//      {
//        pre+=1;
//        if(ppre<2)
//          ppre+=pre;
//      }
//      else 
//      {
//        cur+=pre;
//      }
//      num += ppre+pre;
//      ppre = cur;
//    }
//    else 
//    {
//      pre+=ppre;
//      if(i+1 < 5 && tmp[i] < tmp[i+1])
//      {
//        cur+=pre; 
//      }
//      num += ppre+pre;
//      ppre = cur;
//    }
//    if(i+2 > 5)
//    {
//      if(i+1 < 5)
//      {
//        if(tmp[i+1] > tmp[i])
//        {
//          num += cur;
//        }
//      }
//    }
//  }
//
//  cout << num << endl;
//  return 0;
//}
