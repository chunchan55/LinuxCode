#include"tree.h"

void test1()
{
  int arr[] = {1,2,3,'#','#',4,'#'};
  size_t n = sizeof(arr)/sizeof(arr[0]) - 1;
  Tree tree(arr,n,'#');
  char * str = tree.Serialize(tree.GetRoot());
  int len = strlen(str);
  for(int i = 0; i < len; ++i)
  {
    cout << str[i] << " ";
  }
  cout << "\n";
  tree.PreOrder_N(tree.DeSerialize(str));
  cout << "\n";
}
void test2()
{
  int arr[] = {1,2,3,'#','#',4,'#'};
  size_t n = sizeof(arr)/sizeof(arr[0]) - 1;
  Tree tree(arr,n,'#');
  vector<vector<int>> ans;
  ans = tree.LevelOrder(tree.GetRoot());
  for(int i = 0; i<ans.size();++i)
  {
    for(int j = 0; j < ans[i].size();++j)
    {
      cout<<ans[i][j] << " ";
    }
    cout << endl; 
  }
}
void test3()
{
  int arr[] = {1,2,3,'#','#',4,'#'};
  size_t n = sizeof(arr)/sizeof(arr[0]) - 1;
  Tree tree(arr,n,'#');
  if(tree.IsSymmetrical(tree.GetRoot()) == true)
    cout << "true\n";
  else 
    cout << "false\n";
  int mindepth = tree.MinDepth(tree.GetRoot());
  cout << mindepth << endl;
  int MaxSum = tree.MaxPathSum(tree.GetRoot());
  cout << MaxSum << endl;
}
void test4()
{
  int arr[] = {1,2,3,'#','#',4,'#'};
  size_t n = sizeof(arr)/sizeof(arr[0]) - 1;
  Tree tree(arr,n,'#');
  if(tree.IsSameTree(tree.GetRoot(),tree.GetRoot()) == true)
    cout<<"Is Same\n";
  else
    cout<<"not Same\n";
  tree.PrintbuildTree();
}
void test5()
{

}
int main()
{
  //test();
 // test2();
 // test3();
 test4();
 
  return 0;
}
