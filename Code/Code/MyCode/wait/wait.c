#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

void Mywait()
{
	
}
int main()
{
	pid_t pid = fork();
	if(pid == 0)//child
	{
		sleep(20);
		return 1;
	}
	else //parent
	{
		int st = 12345678;
		int ret = wait(&st);
		if(ret > 0 && (st & 0x7f) == 0)//正常退出
		{
			printf("child exit code:%d\n",ret);
		}
		else if(ret > 0)//异常退出
		{
			printf("sig code :%d\n",st&0x7f);
		}
	}

}
