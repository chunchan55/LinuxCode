#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
void MyHandler(int sig)
{
//什么都不做
	(void)sig;
}

void MySleep(int second)
{
	//使用sigaction 注册一个处理函数
	struct sigaction new_action,old_action;
	new_action.sa_handler = MyHandler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	sigaction(SIGALRM,&new_action,&old_action);
	//调用alarm函数
	alarm(second);
	//调用pause
	pause();
	//扫尾
	sigaction(SIGALRM,&old_action,NULL);
	alarm(0);
}

int main()
{
	while(1)
	{
		printf("hehe\n");
		MySleep(1);
	}
	return 0;
}
