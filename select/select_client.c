#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

static void Usage(const char *proc)
{
	printf("Usage:%s [local_ip] [local_port]\n",proc);
}
int main(int argc,char*argv[])
{
	if(argc!=3){
		Usage(argv[0]);
		return 1;
	}
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0){
		perror("socket");
		return 2;
	}
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0){
		//连接服务器端
		perror("connect");
		return 3;
	}
	dup2(sock,1);//重定向
	while(1)
	{
		char buf[1024];
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s<0){
			buf[s-1] = '\0';
			//write(sock,buf,strlen(buf));
			printf("buf:%s\n",buf);//将数据写到sock文件描述符中
		}
	}
	return 0;
}
