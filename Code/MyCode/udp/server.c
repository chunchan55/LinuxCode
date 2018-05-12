#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
/*一个服务器程序的典型逻辑
 * 1.初始化（制定IP地址和端口号，加载需要的数据文件）
 * 2.进入事件循环（死循环，无限的等待客户端的请求）
 *  （a）读取客户端发送的数据
 *  （b）根据客户端发送的数据进行计算，对于不同用途的服务器，计算的具体逻辑不同，其中的过程很复杂，涉及到几台甚至几十台机器的配合
 *  （c）根据计算出来的最终结果，拼接响应的字符串。
 *   
*/
int main(int argc,char*argv[])
{
	if(argc != 3)// 0 1 2 都被用了
	{
		printf("Usage ./server [ip][port]\n");
		return 1;
	}
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	if(fd < 0)
	{
		perror("socket");
		return 1;
	}
	//socketaddr_t  
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);//将IP地址转换为端口号
	addr.sin_port = htons(atoi(argv[2]));//将主机序转换为网络序
	//上面的转换就是为了 调用bind 把文件描述符和端口号关联在一起
	int ret = bind(fd,(struct sockaddr*)&addr,sizeof(addr));//这里addr取到的就是端口号
	if(ret < 0)
	{
		perror("bind");
		return 1;
	}
	//对于这个程序来说 这个承租要一直执行下去，就需要一个一直执行的程序，就是需要一个 while循环
	while(1)
	{
		//接收数据
		struct sockaddr_in peer_addr;//对端
		socklen_t len = sizeof(peer_addr);
		char buf[1024] = {0};//初始化
		ssize_t read_size = recvfrom(fd,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer_addr,&len);
		if(read_size < 0)
		{
			perror("recvfrom");//不能因为一个错误就不给其他的端口服务
			continue;
		}
		buf[read_size] = '\0';//双重保证
		printf("client port[%s:%d] %s\n",inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port),buf);//又转换为网络字节序inet_ntoa   
	//对于不同的服务器来说，要根据接收到的请求(request)，计算出不同的响应（responsse）
	//此处，由于我们只需要实现一个简单的echo服务器，不需要计算了。
	sendto(fd,buf,strlen(buf),0,(struct sockaddr*)&peer_addr,sizeof(peer_addr));//只有前面一部分是有意义的，所以用strlen
	}
	
}
