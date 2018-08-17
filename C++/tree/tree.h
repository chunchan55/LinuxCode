#include<iostream>
using namespace std;
#include<assert.h>
#include<string>
#include<string.h>
#include<stack>
#include<vector>
#include<queue>
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
  {}
  Tree(int*a,size_t n,const int&invalid)
  {
    assert(a);
    size_t  index = 0;
    _root = CreateTree(a,n,index,invalid);
  }
  Node*CreateTree(int*a,size_t n,size_t& index,const int&invalid)
  {
    Node*root = NULL;
    if(index < n && a[index] != invalid)
    {
      root = new Node(a[index]);
      root->_left = CreateTree(a,n,++index,invalid);
      root->_right = CreateTree(a,n,++index,invalid);
    }
    return root;
  }
  Node*GetRoot()
  {
    return _root;
  }
  void PreOrder_N(Node*root)
  {
    Node*cur = root;
    stack<Node*>s;
    if(cur == NULL)
      return;
    while(cur || !s.empty())
    {
      while(cur)
      {
        cout << cur->_val << " ";
        s.push(cur);
        cur = cur->_left;
      }
      if(!s.empty())
      {
        cur = s.top();
        s.pop();
        cur = cur->_right; 
      }
    }
  }
  //二叉树的层序遍历
  vector<vector<int>> LevelOrder(Node*root)
  {
    vector<vector<int>> tree;
    queue<Node*>q;
    if(root == NULL)
      return tree;
    Node*cur = root;
    q.push(cur);
    while(!q.empty())
    {
      int size = q.size();
    vector<int> num;
      while(size--)
      {
        Node*t = q.front();
        q.pop();
        num.push_back(t->_val);
        if(t->_left)
          q.push(t->_left);
        if(t->_right)
          q.push(t->_right);
      }
      tree.push_back(num);
    }
    return tree;
  }
  //判断二叉树是不是对称的 如果一个树是另一个的镜像，也是对称的
  bool IsSymmetrical(Node*root)
  {
    return IsSymmetrical(root,root);
  }
  bool IsSymmetrical(Node*root1,Node*root2)
  {
    if(root1 == NULL && root2 == NULL)
      return true;
    if(root1 == NULL || root2 == NULL)
      return false;
    if(root1->_val != root2->_val)
      return false;
    return IsSymmetrical(root1->_left,root2->_right) && IsSymmetrical(root1->_right,root2->_left);
  }
char*Serialize(Node*root)
{
  if(root == NULL)
    return "#";
  string r = to_string(root->_val);
  r.push_back(',');
  char*left = Serialize(root->_left);
  char*right = Serialize(root->_right);
  char*ret = new char[strlen(left) + strlen(right) + r.size()];
  strcpy(ret,r.c_str());
  strcat(ret,left);
  strcat(ret,right);
  return ret;
}
Node*DeSerialize(char*str)
{
  return Decode(str);
}
private:
Node*Decode(char*&str)
{
  if(*str == '#')
  {
    str++;
    return NULL;
  }
  int num = 0;
  while(*str != ',')
  {
    num = num*10 + ((*str++) - '0');
  }
  str++;
  Node*root = new Node(num);
  root->_left = Decode(str);
  root->_right = Decode(str);
  return root;
}
};
