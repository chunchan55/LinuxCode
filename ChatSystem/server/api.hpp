#pragma once
#include<strings.h>
#include<iostream>
#include<jsoncpp/json/json.h>
namespace server{
  //此处的Data相当于服务器给客户端提供的API
  struct Data
  {
    std::string name;
    std::string school;
    std::string msg;
  //对于当前情况下，cmd的取值要么为空字符串，要么为quit，如果为quit则标书客户端退出
    std::string cmd;
    void Serialize(std::string* output)//序列化
    {
    //  char buf[1024] = {0};
    //  sprintf(buf,"{name:%s,school:%s,msg:%s,cmd:%s}",name.c_str(),school.c_str(),msg.c_str(),cmd.c_str());
    //  *output = buf;
    //  可以把Json::Value理解为unordered_map
      Json::Value value;
      value["name"] = name;
      value["school"] = school;
      value["msg"] = msg;
      value["cmd"] = cmd;
      Json::FastWriter writer;
      *output = writer.write(value);
      return ;
    }
    void UnSerialize(const std::string& input)
    {
      //std::cout<< "反序列化前" << input.c_str() << std::endl;
      Json::Value value;
      Json::Reader reader;
      reader.parse(input,value);
      if(value["name"].isString())//判定Json对象存储的数据类型是否符合要求
      {
        name = value["name"].asString();
      }
      school = value["school"].asString();
      msg = value["msg"].asString();
      cmd = value["cmd"].asString();
      //std::cout<< "反序列化" << input.c_str() << std::endl;
      return;
    }
  };
}
