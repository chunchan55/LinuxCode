#include"udp_client.h"

udp_client::udp_server(const std::string _ip,const int &_port)
	:ip(_ip)
	,port(_port)
{}
bool udp_client::initclient()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		//打印日志
		perror("socket");
		exit(1);
	}
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ip.c_str());
}
const int &udp_client::sendData(const std::string&instring)
{
	//need ke kap xing 
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ip.c_str());
	ssize_t s = sendto(sock,instring.c_str(),instring.size(),0,(struct sockaddr*)&server,&len);
	if(s>0)
	{
		perror("sendto");//print log
	}
	return s;
}
const int &udp_client::recvData(std::string&outstring)
{
	//need ke kao xing 
	char buf[SIZE];//size 1024
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);
	ssize_t s = recvfrom(sockfd,buf,sizeof(buf),(struct sokaddr*)&remote,&len);
	if(s>0)
	{
		outstring = buf;
	}
	return s;
}
udp_client::~udp_client()
{
	close(sock);
}

