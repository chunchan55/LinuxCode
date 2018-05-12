#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
int main()
{
	pid_t ret = fork();
	if(ret<0)
	{
		perror("fork");
		return -1;
	}
	if(ret==0)
	{
		printf("child pid is %d\n",getpid());
		sleep(10);
	}
	if(ret>0)
	{
		printf("father is %d\n",getpid());
		sleep(5);
		exit(0);
	}
}
