#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/select.h>
#include<stdlib.h>
#include<unistd.h>
int fds[sizeof(fd_set)*8];//定义一个全局数组
static void Usage(const char *proc)
{
	printf("Usage:%s [local_ip] [local_port]\n",proc);
}
int StartUp(const char *ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);//创建TCP套接字
	if(sock<0){
		perror("socket");
		return 2;
	}
	//creat sock sucess
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);
	socklen_t len_server = sizeof(local);
	if(bind(sock,(struct sockaddr*)&local,len_server)<0){
		//服务器绑定自己的IP地址和端口号
		perror("bind");
		return 3;
	}
	//bind sucess
	if(listen(sock,5)<0){
		//将sock变为监听套接字
		perror("listen");
		return 4;
	}
	return sock;
}

int main(int argc,char*argv[])
{
	if(argc!=3){
		Usage(argv[0]);
		return 1;
	}
	int listen_sock = StartUp(argv[1],atoi(argv[2]));
	printf("listen_sock is %d\n",listen_sock);
	int i = 0;
	int nums = sizeof(fds)/sizeof(fds[0]);
	for(i=0;i<nums;++i){
		//给全局的fds赋初值
		fds[i] = -1;
	}
	int maxfd = 0;//最大文件描述符值
	fd_set rfds;//读文件描述符
	while(1)
	{
		struct timeval timeout = {0,0};//设置超时时间，每隔两秒钟记录一次超时时间
	   //struct timeval timeout = {0,0};//以轮询的方式检测
	   FD_ZERO(&rfds);//清空rfds里面所有的文件描述符集
	   fds[0] = listen_sock;
	   maxfd = listen_sock;
	   for(i = 0;i<nums;++i)
	   {
		   if(fds[i]>=0){
			   //置位，说明此时有连接到
			   FD_SET(fds[i],&rfds);
		   }
		   if(fds[i]>maxfd){
			//更新更大的文件描述符值
			maxfd = fds[i];
		   }
	   }
	   switch(select(maxfd+1,&rfds,NULL,NULL,NULL))
	   {
		   case -1:{
			   //select失败
			   perror("select");
			   break;
			}
		   case 0://timeout超时
				printf("timeout...\n");
				break;
			default:
				{
					//least one sock is ready
					for(i=0;i<nums;++i)
					{
						if(fds[i]<0){
						continue;
						}
						if(i==0&&FD_ISSET(fds[0],&rfds)){
						struct sockaddr_in client;
						socklen_t len_client = sizeof(client);
						int newsock = accept(fds[i],(struct sockaddr*)&client,&len_client);
						if(newsock <0){
							perror("accept");
							//continue;
						}
						else{
						printf("get a new client:[%s] [%d]",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
						fflush(stdout);
						int j = 0;
						for(j=0;j<nums;j++)
						{
							if(fds[j]==-1){
							fds[j] = newsock;
							break;
							}
						}
						if(j==nums){
						close(newsock);
						}
					}//else
				}//if
						else if(FD_ISSET(fds[i],&rfds)){
						char buf[1024];
						ssize_t s = read(fds[i],buf,sizeof(buf)-1);
						if(s>0){
						buf[s] = 0;
						printf("client# %s\n",buf);
						}
						else if(s==0){
						printf("the client is quit!!\n");
						close(fds[i]);
						fds[i] = -1;
						}
						else{
						perror("read");
						}
					}//else if
				}//for
			}//deflaut
			break;
	   }//switch
	}//while

	return 0;
}
