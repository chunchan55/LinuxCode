#include<iostream>
#include<string.h>
using namespace std;
class String
{
  private:
    char* _str;
    size_t _size;
    size_t _capacity;
  public:
    String(char* str)
    {
      _capacity = strlen(str);
      _size = _capacity;
      _str = new char[_capacity + 1];
      strcpy(_str,str);
    }
    String(const String&s)
      :_str(NULL)
      ,_size(0)
      ,_capacity(0)
    {
      String tmp(s._str);
      Swap(tmp);
    }
    String&operator = (String s)
    {
      Swap(s);
      return *this;
    }
    ~String()
    {
      if(_str!=NULL)
        delete[]_str;
      _str = NULL;
      _size = 0;
      _capacity = 0;
    }
  private:
    void Swap(String&s)
    {
      swap(_str,s._str);
      swap(_size,s._size);
      swap(_capacity,s._capacity);
    }
};
