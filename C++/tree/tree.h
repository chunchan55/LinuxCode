#include<iostream>
using namespace std;
#include<assert.h>
#include<string>
#include<string.h>
#include<stack>
#include<vector>
#include<queue>
#include<algorithm>
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
//  Node*GetRoot()
//  {
//    return _root;
//  }
//  void PreOrder_N(Node*root)
//  {
//    Node*cur = root;
//    stack<Node*>s;
//    if(cur == NULL)
//      return;
//    while(cur || !s.empty())
//    {
//      while(cur)
//      {
//        cout << cur->_val << " ";
//        s.push(cur);
//        cur = cur->_left;
//      }
//      if(!s.empty())
//      {
//        cur = s.top();
//        s.pop();
//        cur = cur->_right; 
//      }
//    }
//  }
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
  //求二叉树的最小深度
  //1、左为空 右子树 + 1 
  //2、右为空 左子树 +1
  //左右都存在  找出左右子树中较小的深度
  int MinDepth(Node*root)
  {
    if(root == NULL)
      return 0;
    if(root->_left == NULL)
      return MinDepth(root->_right) + 1;
    if(root->_right == NULL)
      return MinDepth(root->_left) + 1;
    int depthL = MinDepth(root->_left);
    int depthR = MinDepth(root->_right);
    return depthL < depthR ? depthL : depthR;
  }
  // 找出最大路径和  不考虑开始节点和结束节点
  int maxValue;
  int MaxPathSum(Node*root)
  {
    if(root == NULL)
      return 0;
    maxValue = -0x7FFFFFFF;
    _MaxPathSum(root);
    return maxValue;
  }
  int _MaxPathSum(Node*root)
  {
    if(root == NULL)
      return 0;
    //找到左边的最大值和右边的最大值  然后 取左右最大值中较大的 + 根
    int LeftMax = max(0,_MaxPathSum(root->_left));
    int RightMax = max(0,_MaxPathSum(root->_right));
    //当前为根 则 maxValue = 根+LM + RM 更新maxValue
    maxValue = max(maxValue,root->_val + LeftMax + RightMax);
    return root->_val + max(LeftMax,RightMax);
  }
  //判断两个树是否相等
  bool IsSameTree(Node*p,Node*q)
  {
    if(p == NULL && q == NULL)
      return true;
    if(p == NULL || q == NULL)
      return false;
    if(p->_val == q->_val)
      return IsSameTree(p->_left,q->_left) && IsSameTree(p->_right,q->_right);
    else 
      return false;
  }

  //根据中序 和 后序 重建二叉树
  //1、后序的最后一个就是根 
  //2、找到中序中的这个根 他的左边是左子树，右边是右子树 
  //3、分为两个区间 根据区间长度 递归 又找到后序中的根 然后 分区间 
  Node* buildTree(vector<int>&inorder,vector<int>&postorder)
  {
    if(inorder.empty())
      return NULL;
    int nodeval = postorder[postorder.size() -1];
    Node*root = new Node(nodeval);
    vector<int>::iterator iter = find(inorder.begin(),inorder.end(),nodeval);//找到中序序列中的那个根 分区间
    vector<int> leftin = vector<int>(inorder.begin(),iter);
    vector<int> rightin = vector<int>(iter+1,inorder.end());
    int l = leftin.size();
    int r = rightin.size();
    if(l > 0)
    {
      vector<int> Ldp = vector<int>(postorder.begin(),postorder.begin()+l);
      root->_left = buildTree(leftin,Ldp);
    }
    if(r > 0)
    {
      vector<int> Rdp = vector<int>(postorder.begin(),postorder.begin() + l + r);
      root->_right = buildTree(rightin,Rdp);
    }
    return root; 
  }
  void PrintbuildTree()
  {
  int arr[5] = {4,2,5,1,3};
  int arr1[5] = {4,5,2,3,1};
  vector<int> inorder;
  vector<int> postorder;
  for(int i = 0; i<5; ++i)
  {
    inorder.push_back(arr[i]);
    postorder.push_back(arr1[i]);
  }
    PreOrder_N(buildTree(inorder,postorder));
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
