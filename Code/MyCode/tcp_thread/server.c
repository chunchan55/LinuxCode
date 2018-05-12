#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct Arg
{
	int new_fd;
	sockaddr_in peer_addr;
}Arg;

void*ThreadEntry(void*arg_ptr)
{
	Arg*arg = (Arg*)arg_ptr;
	int new_fd = arg->new_fd;
	sockaddr_in*peer_addr = &arg->peer_addr;
	while(1)
	{
		//读，，然后断开连接
		//再写回去
		char buf[1024] = {0};
		ssize_t read_size = read(new_fd,buf,sizeof(buf)-1);
		if(read_size < 0)
		{
			perror("read");
			continue;
		}
		if(read_size == 0) //客户端退出
		{
			close(new_fd);
			free(arg);
			break;
		}
		buf[read_size] = '\0';
		printf("[client:%s %d]:%s\n",inet_ntoa(peer_addr->sin_addr),ntohs(peer_addr->sin_port),buf);
		write(new_fd,buf,strlen(buf));
		//timewait  是代码异常
		//closewait  是正常的
		//tcp 三次握手，四次挥手
	}
}
//多进程
void CreateWorker(int new_fd,struct sockaddr_in *addr)
{
	//创建线程
	printf("[client %s:%d] connect\n",inet_ntoa(addr->sin_addr),ntohs(addr->sin_port));

	//创建线程
	pthread_t tid;
	Arg* arg = (Arg*)malloc(sizeof(Arg));
	arg->new_fd = new_fd;
	arg->peer_addr = *addr;
	pthread_create(&tid,NULL,ThreadEntry,arg);
	//线程的分离
	pthread_detach(tid);
//	int ret = fork();
//	if(ret > 0)
//	{
//	//1.父进程中，让该函数能立刻返回，从而能够快速的再次调用到accept
//		return ;
//	}
//	if(ret == 0)
//	{
//	//2.子进程中，循环处理和客户端的数据交互
//		//子进程再创建一个孙子进程，
//		while(1)
//		{
//			char buf[1024] = {0};
//			ssize_t read_size = read(new_fd,buf,sizeof(buf)-1);
//			if(read_size < 0)
//			{
//				perror("read");
//				continue;
//			}
//			if(read_size == 0)
//			{
//				//客户端关闭
//				close(new_fd);
//				break;
//			}
//			buf[read_size] = '\0';
//			printf("[client]%s\n",buf);
//			write(new_fd,buf,strlen(buf));
//		}
//	}
//	else
//	{
//		perror("fork");
//	}
//	
}
int main(int argc,char*argv[])
{
	if(argc != 3)// 0 1 2 都被用了
	{
		printf("Usage ./server [ip][port]\n");
		return 1;
	}
	signal(SIGCHLD,SIG_IGN);//忽略sigchild 信号，就会在进程脱出后，清理子进程
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
		CreateWorker(new_fd,&peer);
	}
	return 0;
}
