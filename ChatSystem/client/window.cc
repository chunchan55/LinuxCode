#include"window.h"
#include<locale.h>
#include "../common/util.hpp"
namespace  client
{
  Window::Window()
  {
    //设置字符编码
    setlocale(LC_ALL,"");
    //对整个ncurses进行初始化
    initscr();
    //隐藏光标
    curs_set(0);
  }
  Window::~Window()
  {
    //对整个ncurses进行销毁
    endwin();
  }
  void Window::DrawHeader()
  {
    int h = LINES/5;//ncurses提供的宏，表示当前窗口的最大行
    int w = COLS; 
    int y = 0;
    int x = 0;
    header_win_ = newwin(h,w,y,x);
    //加上一个边框
    std::string title = "我是一个聊天室";
    PutStrTowin(header_win_,h/2,w/2 - title.size()/2,title.c_str());
    box(header_win_,'|','-');//绘制边框 
    wrefresh(header_win_);
  }
  void Window::DrawInput()
  {
    int h = LINES/5;//ncurses提供的宏，表示当前窗口的最大行
    int w = COLS; 
    int y = LINES*4 / 5;
    int x = 0;
    input_win_ = newwin(h,w,y,x);
    std::string title = "请输入消息";
    //此时的坐标其实是左上角为原点的坐标系
    box(input_win_,'|','-');//绘制边框 
    PutStrTowin(input_win_,1,2,title.c_str());//从1,1开始填充给提示符，是为了和边框不重复，因为边框已经占用了第0行0列
    //加上一个边框
    wrefresh(input_win_);
  }
  void Window::DrawOutput()
  {
    int h = LINES*3/5;
    int w = COLS*3/4;
    int y = LINES/5;
    int x = 0;
    output_win_ = newwin(h,w,y,x);
    box(output_win_,'|','-');
    //刷新之前遍历队列;双端对列，可以任意访问
    for(size_t i = 0; i < msgs_.size(); ++i)
    {
      PutStrTowin(output_win_,i + 1,2,msgs_[i]);
    }
    wrefresh(output_win_);
  }
  void Window:: DrawFriendList()
  {
    int h = LINES * 3 / 5;
    int w = COLS / 4;
    int y = LINES / 5;
    int x = COLS * 3 / 4;
    friend_list_win_ = newwin(h,w,y,x);
    box(friend_list_win_,'|','-');
    //遍历好友列表，把好友信息线束出来
    size_t i = 0;
    for(auto item : friend_list_)
    {
      PutStrTowin(friend_list_win_,i + 1,1,item);
      ++i;
    }
    wrefresh(friend_list_win_);
  }
  void Window:: PutStrTowin(WINDOW* win,int y,int x,const std::string&str)
  {
    mvwaddstr(win,y,x,str.c_str());
  }
  void Window:: GetStrFromWin(WINDOW* win,std::string*str)
  {
    char buf[1024*10] = {0};
    wgetnstr(win,buf,sizeof(buf)-1);//读取
    *str= buf;//对string进行赋值，深拷贝，但是编译器会进行优化，写时拷贝
  }
  void Window:: AddMsg(const std::string&msg)
  {
    //此处，由于我们的窗口显示的消息条数有限，不能无止境的插入新消息，当msgs包含的消息书库
    //超过一定的阈值，就把旧消息删除掉;进程重启，数据就没有了（可以用一个数据库，也可以用文件）
    msgs_.push_back(msg);
    int max_line = LINES * 3 / 5 - 2;
    if(max_line < 3)
    {
      LOG(ERROR) << "max_line too small\n";
      exit(0);
    }
    if(msgs_.size() > max_line)
    {
      msgs_.pop_front();
    }
  }
  void Window::AddFriend(const std::string& friend_info)
  {
   friend_list_.insert(friend_info); 
  }
  void Window::DelFriend(const std::string& friend_info)
  {
    friend_list_.erase(friend_info);
  }
}//end client 
#ifdef TEST_WINDOW
#include<unistd.h>
int main()
{
  client::Window win;
  win.DrawHeader();
  win.DrawInput();
  win.AddMsg("chan1:haha");
  win.AddMsg("chan2:haha");
  win.AddMsg("chan3:haha");
  win.AddMsg("chan4:haha");
  win.AddMsg("chan5:haha");
  win.DrawOutput();
  win.AddFriend("chan1|陕科大");
  win.AddFriend("chan2|陕科大");
  win.AddFriend("chan3|陕科大");
  win.AddFriend("chan4|陕科大");
  win.DrawFriendList();
  sleep(5);
  return 0;
}
#endif
