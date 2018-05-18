#include "chat_server.h"
#include "../common/util.hpp"
#include"api.hpp"
#include<sstream>
namespace server{
  int ChatServer::Start(const std::string&ip,short port)
  {
    //启动服务器没并且进入时间循环；使用udp作为在我们的通信协议
    sock_= socket(AF_INET,SOCK_DGRAM,0);
    if(sock_ < 0)
    {
      perror("socket");
      return -1;
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
    int ret = bind(sock_,(sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
      perror("blind");
      return -1;
    }
//    LOG(INFO) << "Server Start OK!\n";
    //创建两个线程一个从socket中读取数据，一个进行广播
    pthread_t productor,consumer;
    pthread_create(&productor,NULL,Product,this);
    pthread_create(&consumer,NULL,Consume,this);
    pthread_join(productor,NULL);
    pthread_join(consumer,NULL);
    return 0;
  }
  void* ChatServer::Consume(void*arg)
  {
    //生产者线程，做的主要事情就是读取socket中的数据，并且写到BlockQueue中
    ChatServer* server = reinterpret_cast<ChatServer*> (arg);
    //咱们的RecnMsg读取一次数据，并且写到BlockQueue中
    while(true)
    {
      server->RecvMsg();
    }
    return NULL;
  }
  void* ChatServer::Product(void*arg)
  {
    ChatServer* server = reinterpret_cast<ChatServer*> (arg);
    while(true)
    {
      server->BroadCast();
    }
    return NULL;
  }
  int ChatServer::RecvMsg()
  {
    //1.从socket中读取数据
    char buf[1024*5] = {0};
    sockaddr_in peer;
    socklen_t len = sizeof(peer);
    ssize_t read_size = recvfrom(sock_,buf,sizeof(buf)-1,0,(sockaddr*)&peer,&len);
    if(read_size < 0)
    {
      perror("recvfrom");
      return -1;
    }
    buf[read_size] = '\0';
    //2.把数据插入到BlockQueue中
    Context context;
    context.str = buf;
    context.addr = peer;
    queue_.PushBack(context);
    return 0;
  }
  int ChatServer::BroadCast()
  {
    //1.从队列中读取一个元素
    Context context;
    std::string str;
    queue_.PopFront(&context);
    //2.对去除的字符串进行反序列化
    Data data;
    data.UnSerialize(context.str);
    //3.根据这个消息来更新在线好友列表
    if(data.cmd == "quit")
    {
      //b)如果这个成员是一个下线的消息（command事宜个特殊的值）就把这样的一个成员从好友列表中删除
      DelUser(context.addr,data.name);//把哈希表中的 参数传进去
    }
    else
    {
      //a)如果这个成员不在当前好友列表中，加入进来;准备使用[]来进行更新好友列表
      AddUser(context.addr,data.name);
    }
    //4.遍历在线好友列表，把这个数据依次发送给每个客户端
    //由于发送消息的用户也存在于好友列表中，因此在遍历列表的时候也会给自己发送消息，从而达到发送者能够看到自己发送的消息
    //的效果，但是这种实现凡事比较蠢，完全可以控制客户端，不经过网络传输就可以实现这个功能，咱们此处还是用这个蠢方法，
    //更优越的方法交给之后来进行实现
    for(auto item : online_friend_list_)
    {
      SendMsg(context.str,item.second);
    }
   return 0;
  }
  void ChatServer::AddUser(sockaddr_in addr,const std::string&name)
  {
    //这里的key相当于IP地址和用户名进行拼接
    //之所以这样使用，是因为仅仅使用IP可能会出现重复IP的情况（如果N个客户端处在同一个局域网中，那么服务器端看到的IP地址就是相同的，因为NET机制
    std::stringstream ss;
    ss << name << ":" <<addr.sin_addr.s_addr;
    //[] map unordered_map
    //1.如果不存在就插入
    //2.如果存在就修改
    //ValueType& operator[](const KeyType&key)
    //const ValueType& operator(const KeyType& key)const
    online_friend_list_[ss.str()] = addr; 
  }
  void ChatServer::DelUser(sockaddr_in addr,const std::string&name)
  {
    std::stringstream ss;
    ss << name << ":" << addr.sin_addr.s_addr;
    online_friend_list_.erase(ss.str());
  }
  void ChatServer::SendMsg(const std::string&data,sockaddr_in addr)
  {
    //把这个数据通过sendto发送给客户端
    sendto(sock_,data.data(),data.size(),0,(sockaddr*)&addr,sizeof(addr));
  }

}//end serve
