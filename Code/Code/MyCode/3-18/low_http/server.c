#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

void PackageResponse(char http_resp[])
{
	//sprintf  格式化输出
	int cur_len = 0;
	const char*html = "<h1>hello</h1>";
	cur_len += sprintf(http_resp,"HTTP/1.1 200 OK\n");//往缓冲区开始的位置继续写，返回值描述的是泄漏多少个字节
	//将200 改成 404 not found  会有什么现象  
	//302 要加上location： http://www.baidu.com才可以 
	//cur_len += sprintf(http_resp + cur_len,"Location: http://www.baidu.com");
	cur_len += sprintf(http_resp + cur_len,"Content-Length: %lu\n",strlen(html));
	cur_len += sprintf(http_resp + cur_len,"\n");//空行
	cur_len += sprintf(http_resp + cur_len,"<h1>hello</h1>\n");
}
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
	ret = listen(fd,5);//listen的第二个参数的含义
	if(ret < 0)
	{
		perror("listen");
		return 1;
	}

	while(1)
	{
		sockaddr_in peer_addr;
		socklen_t len = sizeof(peer_addr);
		int new_fd = accept(fd,(sockaddr*)&peer_addr,&len);
		if(new_fd < 0)
		{
			perror("accept");
			continue;
		}
	    char buf[100*1024] = {0};
		ssize_t read_size = read(new_fd,buf,sizeof(buf)-1);	
			if(read_size < 0)
			{
				perror("read");
				continue;
			}
			if(read_size == 0)//说明前面的额那个客户端把文件描述符关闭了
			{
				close(new_fd);
				//原有的new_fd 要关闭 ，
				continue;
			}
			buf[read_size] = '\0';
			printf("[Request] %s\n",buf);
			char http_resp[100*1024] = {0};
			PackageResponse(http_resp);
			write(new_fd,http_resp,strlen(http_resp));
			close(new_fd);
	}


}
