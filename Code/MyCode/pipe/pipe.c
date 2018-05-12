#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<errno.h>
#include<string.h>
int main()
{
	int buf[2];
	int ret = pipe(buf);
	if(ret == -1)
	{
		perror("pipe");
		return -1;
	}
	int id = fork();
	char msg[1024] = {0};
	if(id < 0)
	{
		perror("fork");
		return -1;
	}
	if(id == 0)//child
	{	
		//from pipe read
		close(buf[0]);//关闭读端
		while(1)
		{
			ssize_t read_size = read(ret,msg,strlen(msg));
			msg[read_size] = '\0';
		 	if(read_size == 0)
		 	{
		 		printf("read pipe  done\n");
		 		return 0;
		 	}
		 	if(read_size == -1)
		 	{
		 		perror("read");
		 		return -1;
		 	}
			write(1,msg,strlen(msg));
	
		}
	}
	else
	{
		close(buf[1]);//关闭写端
		while(1)
		{
		 	ssize_t read_size = read(0,msg,sizeof(msg)-1);//from stdin read
		 	buf[read_size] = '\0';
		 	if(read_size == 0)
 		 	{
		 		printf("read stdin  done\n");
		  		return 0;
		 	}
 		 	if(read_size == -1)
		 	{
		 		perror("read");
 		 		return -1;
		 	}
		 	write(ret,msg,strlen(msg));//write pipe 
		}
	}

	return 0;
}
