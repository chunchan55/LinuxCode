#pragma once 
#include<string>
#include<unordered_map>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h> 
#include<sstream>
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
namespace http_server
{
  typedef std::unordered_map<std::string,std::string> Header;
  struct Request
  {
    std::string method;
    std::string url;              //例如url为一个形如 http://www.baidu.com/index.html?kwd="cpp"
    std::string url_path;         //index.html
    std::string query_string;     //kwd="cpp"
    //std::string version;        //暂时先不考虑版本号
    Header header;                //一组字符串键值对
    std::string body;             //http的请求body
  };

  struct Response
  {
    int code;                  //状态码
    std::string desc;         //状态码描述
    Header header;           //响应报文中的header数据
    std::string body;       //响应报文中的body
  };

  //当前请求的上下文,包含了这次请求的所有需要的中间数据
  //方便进行扩展，整个处理请求的过程中，每个环节都能够拿到所有和这次请求相关的内容
  class HttpServer;
  struct Context
  {
    Request req;
    Response resp;
    int new_sock;
    HttpServer* server;
  };

  //实现核心服务流程的类
  class HttpServer
  {
    public:
      //以下几个函数返回0 表示成功；返回小于0 表示失败
      int Start(const std::string&ip,short port);
      //根据http请求字符串，来进行反序列化，从socket中读取一个字符串，输出Request对象
      int ReadOneRequest(Context*context);
      //根据Response对象，拼接成一个字符串，写回到客户端
      int WriteOneResponse(Context*context);
      //根据Request对象，构造Response对象 HTTP响应报文中的内容
      int HandlerRequest(Context*context);
      int Process404(Context*context); 
  //   private:
      int ParseFirstLine(const std::string&first_line,std::string*method,std::string*url);
      static void* ThreadEntry(void*arg);
      int ParseUrl(const std::string&url,std::string*url_path,std::string*query_string);
      int ParseHeader(const std::string&header_line,Header*header);
      void PrintRequest(const Request&req);
  };
}//end http_server 
