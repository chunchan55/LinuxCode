#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

//./client [ip][port] 服务器的端口号
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
int main(int argc,char*argv[])
{
	if(argc != 3)// 0 1 2 都被用了
	{
		printf("Usage ./client [ip][port]\n");
		return 1;
	}
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	if(fd < 0 )
	{
		perror("socket");
		return 1;
	}
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	//循环  客户端不需要进行bind
	char buf[1024] = {0};
	sockaddr_in peer;
	while(1)
	{
		//从标准输入里读
		socklen_t len = sizeof(peer);
		printf("please Enter# ");
		fflush(stdout);//刷新标准输出
		ssize_t read_size = read(0,buf,sizeof(buf)-1);
		if(read_size < 0)
		{
			perror("read");
			return 1;//这里就直接错误就退出，因为一个服务器只有一个客户端
		}
		buf[read_size] = '\0';
		ssize_t write_size = sendto(fd,buf,strlen(buf),0,(sockaddr*)&server_addr,sizeof(server_addr));
		if(write_size < 0)
		{
			perror("sendto");
			return 1;
		}
		char buf_recv[1024] = {0};
		read_size = recvfrom(fd,buf_recv,sizeof(buf_recv)-1,0,(sockaddr*)&server_addr,&len);
		if(read_size > 0)
		{
			buf[read_size] = '\0';
			printf("server response # %s\n",buf_recv);
		}
	}
}
