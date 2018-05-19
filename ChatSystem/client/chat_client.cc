#include"chat_client.h"
namespace client{
  //这里IP和port是通过命令行参数传进来的
  //如果需要通过配置文件中读取IP和port，如何修改
  //（可以使用json来组织配置格式）
  //{
  //ip:127.0.0.1\
  //port:9090
  //}
  int ChatClient::Init(const std::string&server_ip,short server_port)
  {
    sock_ = socket(AF_INET,SOCK_DGRAM,0);
    if(sock_ < 0)
    {
      perror("socket");
      return -1;
    }
    //相当于把IP和端口号保存为一个变量中，后续好使用
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_addr.s_addr = inet_addr(server_ip.c_str());
    server_addr_.sin_port = htons(server_port);
    return 0;
  } 
  int ChatClient:: SetUserInfo(const std::string&name,const std::string&school)
  {
    name_ = name;
    school_ = school; 
    return 0; 
  }
  void ChatClient:: SendMsg(const std::string&msg)
  {
    //按照下面这种方式来发送是错误的！
    //客户端和服务器交互接口要严格按照服务器提供的api来操作
    //这样的约定就相当于定制了一种应用层协议
   //sendto(sock_,msg.c_str(),msg.size(),0,(sockaddr*)&server_addr_,sizeof(server_addr_));
    server::Data data;
    data.name = name_;
    data.school = school_;
    data.msg = msg;
   // std::cout<< "msg" << data.msg << "name" << data.name << std::endl;
    //以下的逻辑相当图约定了用户输入什么样的内容表示要进行下线
    if(data.msg == "quit" || data.msg == "exit" || data.msg == "Q")
    {
      data.cmd = "quit";
    }
    std::string str;
    data.Serialize(&str);
    //以上是数据的准备工作，以下才是发送数据
    sendto(sock_,str.c_str(),str.size(),0,(sockaddr*)&server_addr_,sizeof(server_addr_));
    //std::cout << "str.c_str: " << str.c_str() << "str.size: " << str.size() << std::endl;
    return; 
  }
  void ChatClient:: RecvMsg(server::Data*data)
  {
   // printf("RecvMsg begin\n");
    char buf[1024*10] = {0};
    //接收从服务器返回来的数据;
    //由于对端的IP端口号就是服务器的IP端口号，所以此处没必要再获取一遍对端的IP，这部分内容已经都知道了
    ssize_t read_size = recvfrom(sock_,buf,sizeof(buf)-1,0,NULL,NULL);
    if(read_size < 0 )
    {
      perror("recvfrom");
      return;
    }
    //std::cout << sock_ << std::endl;
    //std::cout << "read_size:" << read_size << std::endl;
    buf[read_size] = '\0';
    data->UnSerialize(buf);
    // std::cout << "buf:" << buf << std::endl;
    //  printf("RecvMsg finish\n");
    return;

  }
}//end client 


///先实现一个建议版本的客户端，通过这个简易版本的客户端来进行测试

#include<iostream>
void* Send(void* arg)
{
  //循环发送数据
  client::ChatClient* client = reinterpret_cast<client::ChatClient*>(arg);
  while(true)
  {
    std::string str;
    std:: cin >> str;
    client->SendMsg(str);
   // std::cout<< "Send" << str.c_str() << std::endl;
  }
  return NULL;
}
void* Recv(void* arg)
{
  //循环接收数据
  client::ChatClient* client = reinterpret_cast<client::ChatClient*>(arg);
  while(true)
  {
    server::Data data;
    client->RecvMsg(&data);
    //把接收到的消息打印出来
    std::cout << "{" << data.name.c_str() << "|" << data.school.c_str() << "}" << data.msg.c_str() << "\n"; 
  }
  return NULL;
}

int main(int argc,char*argv[])
{
  if(argc != 3)
  {
    printf("Usage ./client [ip] [port]\n");
    return 1;
  }
  client::ChatClient client;
  client.Init(argv[1],atoi(argv[2]));
  std::string name,school;
  std::cout<<"输入用户名：";
  std::cin >> name;
  std::cout << "输入学校："; 
  std::cin >> school;
  client.SetUserInfo(name,school);

  //std::string str;
  //std::cin >> str;
  //client.SendMsg(str);
  //server::Data data;
  //client.RecvMsg(&data);
  //创建两个线程，分别进行发送数据和接收数据
  pthread_t stid,rtid;
  pthread_create(&stid,NULL,Send,&client);
  pthread_create(&rtid,NULL,Recv,&client);
  pthread_join(stid,NULL);
  pthread_join(rtid,NULL);
  return 0;
}
