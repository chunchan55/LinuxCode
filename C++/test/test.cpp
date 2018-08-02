#include<iostream>
using namespace std;

//相邻两个小朋友，成绩较高的比较低的多一个贴纸
int main()
{
  int tmp[5];
  for(int i = 0; i< 5; i++)
  {
    cin >>  tmp[i];
  }
  int num = 0;
  int i = 1;
  int ppre = 1;
  int pre = 1;
  for(i = 1; i<5; i+=2)
  {
    int cur = 1;
    if(tmp[i-1] > tmp[i])
    {
      if(ppre >1)
        pre = 1;
      if(i+1 < 5 && tmp[i]>tmp[i+1])
      {
        pre+=1;
        if(ppre<2)
          ppre+=pre;
      }
      else 
      {
        cur+=pre;
      }
      num += ppre+pre;
      ppre = cur;
    }
    else 
    {
      pre+=ppre;
      if(i+1 < 5 && tmp[i] < tmp[i+1])
      {
        cur+=pre; 
      }
      num += ppre+pre;
      ppre = cur;
    }
    if(i+2 > 5)
    {
      if(i+1 < 5)
      {
        if(tmp[i+1] > tmp[i])
        {
          num += cur;
        }
      }
    }
  }

  cout << num << endl;
  return 0;
}
