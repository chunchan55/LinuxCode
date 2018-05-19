#include"http_server.h"
#include"util.hpp"
namespace http_server{
  int HttpServer::Start(const std::string&ip,short port)
  {
    int listen_sock = socket(AF_INET,SOCK_STREAM,0);
    if(listen_sock < 0)
    {
      perror("socket");
      return -1;
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
    int ret = bind(listen_sock,(sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
      perror("bind");
      return -1;
    }
    ret = listen(listen_sock,5);
    if(ret < 0)
    {
      perror("listen");
      return -1;
    }
    //printf("ServerStart OK!\n");
    LOG(INFO) << "ServerStart OK!\n";
    //TODO
    return 0;
  }
  //根据http请求字符串，来进行反序列化，从socket中读取一个字符串，输出Request对象
  int ReadOneRequest(Context*context);
  //根据Response对象，拼接成一个字符串，写回到客户端
  int WriteOneResponse(Context*context);
  //根据Request对象，构造Response对象
  int HandlerRequest(Context*context);
}
