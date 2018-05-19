#pragma once 
#include<string>
#include<unordered_map>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include "block_queue.hpp"
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
namespace server
{
  struct Context{
    std::string str;
    sockaddr_in addr;
  };
  class ChatServer
  {
    public:
      int Start(const std::string&ip,short port);
      int RecvMsg();//接收消息
      int BroadCast();
    private:
      static void* Consume(void*);//生产者
      static void* Product(void*);//消费者
      void AddUser(sockaddr_in adr,const std::string&name);
      void DelUser(sockaddr_in adr,const std::string&name);
      void SendMsg(const std::string&str,sockaddr_in addr);;
      //key 内容用户身份标识，IP+昵称
      //value ip+端口号（struct sockaddr_in）
      std::unordered_map<std::string,sockaddr_in> online_friend_list_;//好友列表
      //TODO 实现一个队列，作为交易场所 使用一个阻塞队列来作为生产者消费者模型的交易场所
      BlockQueue<Context> queue_; 
      int sock_;//文件描述符，服务器进行绑定的

  };

}//end server
