#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int argc,char*argv[])
{
	if(argc != 3)// 0 1 2 都被用了
	{
		printf("Usage ./server [ip][port]\n");
		return 1;
	}
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0)
	{
		perror("socket");
		return 1;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));
	//int tmp = bind(fd,(struct sockaddr*)&addr,sizeof(addr));
//	if(tmp < 0)
//	{
//		perror("bind");
//		return 1;
//	}
	int ret = connect(fd,(struct sockaddr*)&addr,sizeof(addr));

	if(ret < 0)
	{
		perror("connect");
		return 1;
	}
	while(1)
	{
		char buf[1024] = {0};
		ssize_t read_size = read(0,buf,sizeof(buf)-1);
		if(read_size < 0)
		{
			perror("read");
			continue;
		}
		if(read_size == 0)
		{
			printf("goodbye\n");
			break;
		}
		buf[read_size] = '\0';
		write(fd,buf,strlen(buf));
		char buf_output[1024] = {0};
		read_size = read(fd,buf_output,sizeof(buf_output)-1);
		
		if(read_size < 0)
		{
			perror("read");
			continue;
		}
		if(read_size == 0)
		{
			printf("peer close\n");
			break;
		}
		buf_output[read_size] = '\0';
		printf("server response:%s\n",buf_output);
	}
	close(fd);
	return 0;
}
