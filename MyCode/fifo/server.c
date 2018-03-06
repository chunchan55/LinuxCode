#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
int main()
{
	int ret = mkfifo("./myfifo",0666);
	if(ret == -1)
	{
		perror("mkfifo");
		return -1;
	}
	int fd = open("./myfifo",O_RDONLY);//read zuseshidu
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	printf("open ok\n");
	while(1)
	{
		char buf[1024] = {0};
		ssize_t read_size = read(fd,buf,sizeof(buf)-1);
		if(read_size == 0)
		{
			printf("read done\n");
			return 0;
		}
		if(read_size == -1)
		{
			perror("read");
			return -1;
		}
		buf[read_size] = '\0';
		printf("client:%s",buf);
		//fflush(stdout);
	}
	close(fd);
}

