#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	pid_t pid = vfork();
		return 0;
	if(pid == 0)
	{
		printf("child\n");
		return 0;
	}
	if(pid == -1)
	{
		perror("vfork");
		exit(1);
	}
	else
	{
		printf("father\n");
		exit(1);
	}
	return 0;
}
