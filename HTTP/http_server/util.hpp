///////////////////////////////////////////////////////////////////////////////////////////////////////////
//此文件防止一些公共的工具类和函数；为了让这些工具用的方便，直接把声明和实现都放在.hpp中
////////////////////////////////////////////////////////////////////////////////////////////////////////// 

#pragma once 
#include<iostream>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<vector>
#include<boost/algorithm/string.hpp>
//这些工具类是为了提供方便而已，可以不需要对象来调用的，所以可以使用静态成员函数
class TimeUtil
{
  public:
    static int64_t TimeStamp()//获取到当前的秒级时间戳
    {
      struct timeval tv;
      gettimeofday(&tv,NULL);
      return tv.tv_sec;
    }
    //获取到微秒级
    static int64_t TimeStampUS()//获取到当前的秒级时间戳
    {
      struct timeval tv;
      gettimeofday(&tv,NULL);
      return 1000 * 1000 * tv.tv_sec + tv.tv_usec;//换算成微秒
    }
    
};
enum LogLevel
{
  INFO,
  WARNING,
  ERROR,
  CRITIAL,//致命错误
  DEBUG,
};
//LOG(INFO) <<""
//内联：
inline std::ostream& Log(LogLevel level,const char*file,int line)
{
  std::string prefix = "I";
  if(level == WARNING)
  {
    prefix = "W";
  }
  else if(level == ERROR)
  {
    prefix = "E";
  }
  else if(level == CRITIAL)
  {
    prefix = "C";
  }
  else if(level == DEBUG)
  {
    prefix = "D";
  }
  std::cout << "[" << prefix << TimeUtil::TimeStamp() << " " << file << ":" << line << "]";
  return std::cout;
}

//__FILE__ __LINE__
//为什么用宏，用函数不可以吗？行列就会被写死
#define LOG(level) Log(level,__FILE__,__LINE__)

class FileUtil
{
  public:
    //从文件描述符中读取一行。一行的界定标识是 \n \r \r\n
    //返回的line 中不包含界定标识的 
    //例如 aaa\nbbb\nccc
    //调用ReadLine返回的line对象的内容为aaa,不包含\n
    static int ReadLine(int fd,std::string*line)
    {
      line->clear();
      while(true)
      {
        char c = '\0';
        ssize_t read_size = recv(fd,&c,1,0);
        if(read_size < 0)
        {
          return -1;
        }
        //如果当前字符是\r把这个情况处理成\n
        if(c == '\r')
        {
          recv(fd,&c,1,MSG_PEEK);//表示虽然从缓冲区中读了一个字符，但是缓冲区并没有把他删掉
          if(c == '\n')
          {
            recv(fd,&c,1,0);//发现\r 后面一个字符刚好就是\n,为了不影响下次循环，就需要把这样的字符重缓冲区中干掉
            break;
          }
          else
            c = '\n';
        }
        if(c == '\n')
          break;
        line->push_back(c);
      }
      return 0;
    }
   static int ReadN(int fd,size_t len,std::string*output)
    {
      output->clear();
      char c = '\0';
      for(size_t i = 0; i< len; ++i)
      {
        recv(fd,&c,1,0);
        output->push_back(c);
      }
      return 0;
    }
};

class StringUtil
{
  //把一个字符串按照split_char 进行切分，分成N个子串，放到output数组中
  //token_compress_on 的含义是：例如分隔符是空格，字符串是"a b"
  //对于打开压缩情况，返回的子串就是有两个，"a","b"
  //token_compress_of
  //对于关闭压缩的情况就是有三个字符串
  public:
 static int Split(const std::string&input,const std::string&split_char,std::vector<std::string>*output)
  {
    boost::split(*output,input,boost::is_any_of(split_char),boost::token_compress_on);
    return 0;
  }
};
