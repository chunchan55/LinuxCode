/*************************************************************************
	> File Name: vfork.c
	> Author: chan
	> Mail: 1946429765@qq.com 
	> Created Time: Mon 27 Nov 2017 08:03:58 PM CST
 ************************************************************************/


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
int main()
{
	pid_t ret = vfork();
	if(ret>0)//父亲
	{
		printf("i am father:%d\n",getpid());
	}
	else if(ret==0)//孩子
	{
		printf("i am child:start%d\n",getpid());
		sleep(5);
		printf("i am child:finish:%d\n",getpid());
		exit(0);
	}
	else
	{
		perror("vfork");
	}
	//printf("ret = %d, pid = %d, ppid = %d\n",ret,getpid(),getppid());
	return 0;
}
