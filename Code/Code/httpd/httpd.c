#include"httpd.h"

const char *status_line = "HTTP/1.0 200 OK\r\n";
const char *blank_line = "\r\n";
int startup(const char*ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		//print_log(strerror(errno),FATAL);
		return 2;
	}// creat sock success
	int opt = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);
//	socklen_t len_server = sizeof(local);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local)))
	{
//		print_log(strerror(errno),FATAL);
		return 3;
	}
	if(listen(sock,10))
	{
	//	print_log(strerror(errno),FATAL);
		return 4;
	}
	return sock;
}
//把所有的换行 \ \r 都转换成\n
static int get_line(int sock,char line[],int size)
{
	//read 1 char,one by one
	char c = '\0';
	int len = 0;
	while(c!='\n'&& len<size-1)
	{
		ssize_t r = recv(sock,&c,1,0);
		if(r>0)
		{
			if(c=='\r')
			{
				recv(sock,&c,1,MSG_PEEK);
				if(c=='\n')
				{
					recv(sock,&c,1,0);
				}				
				else
				{
					c = '\n';
				}
			}
			line[len++] = c;
		}
		else
		{
			return -1;
		}
	}
	line[len] = 0;
	return len;
}

static int echo_string(int sock)
{}
void error_response(int sock,int err_code)
{}
static int echo_www(int sock,const char *path,int size)
{
	int fd = open(path,O_RDONLY);
	if(fd<0)
	{
		//print_log(strerror(errno),FATAL);
		perror("open");
		return 404;
	}
	//const char*status_line = "HTTP/1.0 200 OK\r\n";//正文
	send(sock,status_line,strlen(status_line),0);
	//const char *blank_line = "\r\n";//空行  定义为全局的
	send(sock,blank_line,strlen(blank_line),0);
	if(sendfile(sock,fd,NULL,size)<0)
	{
		//print_log(strerror(errno),FATAL);
		return;
	}
	close(fd);
}
void handler_handler(int sock)
{
	char buf[SIZE];
	int ret = -1;
	do
	{
		ret = get_line(sock,buf,sizeof(buf));
	}
	while(ret>0&&strcmp(buf,"\n") != 0);
}
static void drop_handler(int sock)
{
	
}

void *handler_request(void *arg)
{
	int sock = (int)arg;
	//char buff[SIZE];
	int ret = 0;
	char buf[SIZE];
	char method[SIZE/10];
	char url[SIZE];
	char path[SIZE];
	int i,j;
	int cgi = 0;
	char *query_string = NULL;
	int err_code = 200;
#ifdef _STDOUT_
	//char buf[4096];
	ssize_t s = read(sock,buf,sizeof(buf)-1);
	buf[s] = 0;
	printf("client:s%",buf);
#endif
	if(get_line(sock,buf,sizeof(buf))<=0)
	{
		err_code = 404;
		goto end;
	}
	printf("%s",buf);
	//GET/HTTP/1.0
	i = 0;//method ->index
	j = 0;//buf ->index
	while(!isspace(buf[j])&&j<sizeof(buf)&&i<sizeof(method)-1)
	{
		method[i] = buf[j];
		i++;
		j++;
	}
	method[i] = 0;
	while(isspace(buf[j])&&j<sizeof(buf))
	{
		j++;
	}
	i = 0;//重置i 让他从头开始 
	while(!isspace(buf[j]) && j< sizeof(buf) &&i< (sizeof(url)-1))
	{
		url[i] = buf[j];//提取URL中的信息
		i++;
		j++;
	}
	url[i] = 0;
	if(strcasecmp(method,"GET")&&strcasecmp(method,"POST"))
	{
		err_code = 404;
		goto end;
	}
	if(strcasecmp(method,"POST")==0)
	{
		cgi = 1;
	}
	else 
	{
		query_string = url;
		while(*query_string)
		{
			//判断是否有参数 以？作为标志，有参数就++
			if(*query_string=='?')
			{
				*query_string = '\0';
				query_string++;
				cgi = 1;
				break;
			}
			query_string++;
		}
	}
	sprintf(path,"wwwroot%s",url);
	//method,url,query_string,cgi
	if(path[strlen(path)-1]=='/')
	{
		strcat(path,"index.html");
	}
	struct stat st;
	if(stat(path,&st)<0)
	{
		err_code = 404;
		goto end;
	}
	else 
	{
		if(S_ISDIR(st.st_mode))
		{
			strcat(path,"/index.html");
		}
		else if((st.st_mode & S_IXUSR)||(st.st_mode & S_IXGRP)||(st.st_mode & S_IXOTH))
		{
			cgi = 1;
		}
		else 
		{
		}
		//ok->cgi =?,path,query_string,method 
		if(cgi)
		{
			//exe_cgi(sock,method,path,query_string);
		}
		else
		{
			//printf("method:%s,url:%s,path:%s,cgi:%d,query_string:%s\n",method,url,path,cgi,querl_string);
			//drop_handler(sock);
			handler_handler(sock);
			err_code = echo_www(sock,path,st.st_size);
		}
	}
end:
	if(err_code!=200)
	{
		error_response(sock,err_code);
	}
	close(sock);
	return (void*)0;
}

