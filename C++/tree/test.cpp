#include"tree.h"

void test()
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
int main()
{
  test();
  return 0;
}
