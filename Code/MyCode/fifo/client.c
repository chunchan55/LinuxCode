#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
int main()
{
	int fd  = open("./myfifo",O_WRONLY);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}
	while(1)
	{
		//from stdin read
		char buf[1024] = {0};
		//scanf("%s",buf);
		//fflush(stdin);
		ssize_t read_size = read(0,buf,sizeof(buf)-1);
		if(read_size < 0)
		{
			perror("read");
			return -1;
		}
		buf[read_size] = '\0'; 
		ssize_t write_size = write(fd,buf,strlen(buf)+1);
		if(write_size == -1)
		{
			perror("write");
			return -1;
		}
	}
	close(fd);
}
