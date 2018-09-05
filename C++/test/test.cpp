#include <iostream>
using namespace std;
#include<string.h>
#include<math.h>
#include<string>
void ReverseWord(string&str,int l,int r);

string ReverseSentence(string str)
{
  size_t size = str.size();
  if(size == 0)
    return "";
  int mark = 0;
  str += ' ';
  for(int i = 0; i<size+1; ++i)
  {
    if(str[i] == ' ')
    {
      ReverseWord(str,mark,i-1);
      mark = i+1;
    }
  }
  str = str.substr(0,size);
  ReverseWord(str,0,size-1);
  return str;
}

void ReverseWord(string&str,int l,int r)
{
  while(l < r)
  {
    swap(str[l],str[r]);
    ++l;
    --r;
  }
}
int main()
{
  string str;
  cin >> str;
  string res = ReverseSentence(str);
  cout << str.c_str() << endl;
  return 0;
}
//求数组中连续子数组的
//int FindMaxSum(vector<int> arr)
//{
//  if(arr.empty())
//    return 0;
//  int n = arr.size();
//  vector<int> f(n,0);
//  f[0] = arr[0];
//  for(int i =1; i<n; ++i)
//  {
//    f[i] = max(f[i-1]+arr[i],arr[i]);
//  }
//  int result = f[0];
//  for(int i = 1; i<n; ++i)
//  {
//    result = max(f[i],result);
//  }
//  return result;
//}
//
//int main()
//{
//  int n = 0;
//  cin >> n;
//  int arr[n];
//  for(int i = 0; i<n; ++i)
//  {
//    cin >> arr[i];
//  }
//  vector<int> a;
//  for(int i = 0; i<5; ++i)
//  {
//    a.push_back(arr[i]);
//  }
//  int res = FindMaxSum(a);
//  cout << res << endl;
//  return 0;
//}


//#include <iostream>
//using namespace std;
//int main(){
//    int n,curSum=0,maxSum=-0x7FFFFFFF;
//    cin>>n;
//    int arr[n];
//    for(int i=0;i<n;i++){
//        cin>>arr[i];
//        curSum+=arr[i];
//        if(curSum>maxSum){
//            maxSum=curSum;
//        }
//        if(curSum<0){
//            curSum=0;
//        }
//    }
//    cout<<maxSum<<endl;
//    return 0;
//}
//
//
//#include<iostream>
//using namespace std;
//#include<string.h>
//#include<string>
//int Find(string str)
//{
//	int len = str.size();
//	int hashtable[1024] = {0};
//	for(int i = 0; i<len; ++i)
//	{
//		hashtable[str[i]]++;
//	}
//	for(int j = 0; j<len; j++)
//	{
//		if(hashtable[str[j]] == 1)
//		{
//			return j;
//		}
//	}
//	return -1;
//}
//int main()
//{
//	string s;
//	cin >> s;
//	int tmp = Find(s);
//	if(tmp == -1 )
//		cout << "-1\n";
//	else
//		cout << s[tmp]<< endl;
//	return 0;
//}
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
