#include<stdio.h>
#include<unistd.h>
int main()
{
	pid_t ret = fork();
	if(ret>0)//父亲
	{
		printf("i am father:%d\n",getpid());
	}
	else if(ret==0)//孩子
	{
		printf("i am child:%d\n",getpid());
	}
	else
	{
		//error
	}
	//printf("ret = %d, pid = %d, ppid = %d\n",ret,getpid(),getppid());
	return 0;
}
