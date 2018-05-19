///////////////////////////////////////////////////////////////////////////////////////////////////////////
//此文件防止一些公共的工具类和函数；为了让这些工具用的方便，直接把声明和实现都放在.hpp中
////////////////////////////////////////////////////////////////////////////////////////////////////////// 

#pragma once 
#include<iostream>
#include<sys/time.h>

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
  std::cout << "[" << prefix << TimeUtil::TimeStamp() << " " << file << ":" << line << "]";
  return std::cout;
}

//__FILE__ __LINE__
//为什么用宏，用函数不可以吗？行列就会被写死
#define LOG(level) Log(level,__FILE__,__LINE__)
