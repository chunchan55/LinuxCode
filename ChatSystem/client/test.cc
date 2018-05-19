//单例模式
//饿汉模式

//class Singleton
//{
//  public:
//    static Object*Instance()
//    {
//      return &obj;
//    }
//  private:
//    class Object
//    {
//      private:
//        int data;
//        //XXX
//    };
//    static Object obj;
//};

//懒汉模式

class Singleton
{
  private:
    class Object
    {
      private:
        int data;
        //XXX
    };
    static Object*obj;
  public:
    static Object*Instance()
    {
      //既想线程安全，又不想有很多开销，双重判定
      if(obj == NULL)
      {
        lock();//加锁
        if(obj == NULL){
        obj = new Object();
        }
      }
      unlock();//解锁
      return obj;
    }
};

Object* Singleton::obj = NULL;//静态成员变量要进行初始化
