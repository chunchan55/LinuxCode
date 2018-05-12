#include"window.h"
window::window()
{
	initscr();
}
window::~window()
{
	endwin();
}
drawHeader()
{
	int h = LINES/5;
	int w = COLS/4;
	int y = 0;
	int x = 0;
	header = newwin(h,w,x,y);
	box(header,'+''.');//+ . 就是窗口的风格
}
drawOutput()
{

	int h = (LINES*3)/5;
	int w = (COLS*3)/4;
	int y = LINES/5;
	int x = 0;
	header = newwin(h,w,x,y);
	box(output,'+''.');//+ . 就是窗口的风格
}
drawFlist()
{

	int h = (LINES*3)/5;
	int w = COLS/4;
	int y = (LINES*5)/4;
	int x = 0;
	header = newwin(h,w,x,y);
	box(flist,'+''.');//+ . 就是窗口的风格
}
drawInput()
{
	
	int h = LINES/5;
	int w = COLS;
	int y = (LINES*4)/5;
	int x = 0;
	header = newwin(h,w,x,y);
	box(input,'+''.');//+ . 就是窗口的风格
}

window::void putstrtowin(WINDOW*win,int y,int x,std::string&str)
{
	mvwaddstr(win,y,x,str.c_str());
}//可以有一个光标
window::void getstrfromwin(WINDOW* win,std::string&str)
{
	
}//输入数据

int main()
{
	window w;
	std::string tis = "whlcome to chat_system!";
	int i = 1;
	int y,x;
	int dir = 0;
	while(1){
		getmaxyx(w.header,y,x);
		w.drawHeader();
		w.putstrtowin(w.header,1,i,tips);
		wrefresh(w.header);//把数据刷新出来
		usleep(200000);
		if(dir == 0)
		{
			i++;
			if(i >= tips.size())
			{
				dir = 1;
			}
		}
		if(dir == 1)
		{
			i--;
			if(i<=1)
			{
				dir = 0;
			}
		}
	}
	return 0;
}
















