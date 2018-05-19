#pragma once
#include "../server/api.hpp"
#include<string>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
namespace client{
  class ChatClient
  {
    public:
      //客户端的初始化;调用socket等其他复杂的函数
      int Init(const std::string&server_ip,short server_port);
      //设置用户信息
      //让客户端启动的时候提示用户输入姓名学校；然后从标准输入中读取
      int SetUserInfo(const std::string&name,const std::string&school);
      //发送消息
      void SendMsg(const std::string&msg);
      //接收消息 本质上接收到的内容也是json格式的内容
      void RecvMsg(server::Data*data);
    private:
      //这个文件描述符用来保存和服务器交互的socket，通过Init函数创建好，交给SendMsg和RecvMsg直接使用
      int sock_;
      //把服务器端传过来的IP地址和端口号都保存下来，后序使用
      sockaddr_in server_addr_;
      std::string name_;
      std::string school_;
  };
}
