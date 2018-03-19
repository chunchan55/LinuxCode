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
	int ret = bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret < 0)
	{
		perror("bind");
		return 1;
	}
	///上面的代码和udp是一样的
	ret = listen(fd,5);//listen的第二个参数的含义
	if(ret < 0)
	{
		perror("listen");
		return 1;
	}
	while(1)
	{
		struct sockaddr_in peer;//对端
		socklen_t len = sizeof(peer);
		int new_fd = accept(fd,(struct sockaddr*)&peer,&len);
		if(new_fd < 0)
		{
			perror("accept");
			continue;
		}
		while(1)
		{	
			char buf[1024] = {0};
			ssize_t read_size = read(new_fd,buf,sizeof(buf)-1);//会有一个新的fd
			if(read_size < 0)
			{
				perror("read");
				continue;
			}
			if(read_size == 0)//说明前面的额那个客户端把文件描述符关闭了
			{
				printf("client close\n");
				//原有的new_fd 要关闭 ，
				continue;
			}
			buf[read_size] = '\0';
			printf("[%s:%d] %s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
			write(new_fd,buf,strlen(buf));
		}
		close(new_fd);
	}
	return 0;
}
