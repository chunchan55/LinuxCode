#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
int main()
{
	pid_t pid = getpid();
	pid_t id = fork();
	if(id<0)
	{
		perror("fork");
		return -1;
	}
	else if(id>0)
	{//father
		printf("father pid is:%d,return pid is:%d\n",getpid(),id);
		sleep(5);
	}
	else if(id==0)
	{
		printf("child pid is:%d\n",getpid());
		exit(3);
	}
}
