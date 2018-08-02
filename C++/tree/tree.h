#include<iostream>
using namespace std;

struct TreeNode
{
  TreeNode*_left;
  TreeNode*_right;
  int _val;
  TreeNode(const int& val)
    :_left(NULL)
     ,_right(NULL)
     ,_val(val)
  {}
};

class Tree 
{
  typedef TreeNode Node;
  private:
  Node*_root;
  public:
  Tree()
    :_root(NULL)
  {

  }
};
