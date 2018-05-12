#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define SIZE 10240

//创建一个结构体类型，里面保存有一个文件描述符和一段缓冲区
typedef struct epbuf
{
	int fd;
	char buf[SIZE];
}epbuf_t,*epbuf_p,**epbuf_pp;

static epbuf_p alloc_epbuf(int fd)
{
	epbuf_p ptr = (epbuf_p)malloc(sizeof(epbuf_t));
	if(ptr==NULL)
	{
		perror("malloc");
		return 6;
	}
	ptr->fd = fd;
	return ptr;
}

static void del_epbuf(epbuf_p ptr)
{
	if(ptr!=NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

int startup(const char*ip,int port)
{
	
}
