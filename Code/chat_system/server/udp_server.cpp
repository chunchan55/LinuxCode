#include"udp_server.h"

udp_server::udp_server(const std::string _ip,const int &_port)
	:ip(_ip)
	,port(_port)
{}
bool udp_server::initserver()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		//打印日志
		perror("socket");
		exit(1);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip.c_str());
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		exit(2);
	}
}
const int &udp_server::sendData(const std::string&instring,struct sockaddr_in &remote,socklen_t &len)
{
	//need ke kap xing 
	ssize_t s = sendto(sock,instring.c_str(),instring.size(),0,(struct sockaddr*)&remote,&len);
	if(s>0)
	{
		perror("sendto");//print log
	}
	return s;
}
void udp_server::adduser(const struct sockaddr_in &remote)
{
	online_user.insert(std::pair<int,struct sockaddr_in>((int)remote.sin_addr.s_addr,remote));
}
const int &udp_server::recvData(std::string&outstring)
{
	//need ke kao xing 
	char buf[SIZE];//size 1024
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);
	ssize_t s = recvfrom(sockfd,buf,sizeof(buf),(struct sokaddr*)&remote,&len);
	if(s>0)
	{
		adduser(remote);
		outstring = buf;
		pool.putdata(outstring);
	}
}
int udp_server::brocast()
{
	std::string msg;
	pool.getdata(msg);
	std::map<int,struct sockaddr_in>::iterator iter = online_user.begin();
	socklen_t len = 0;
	for(;iter != online_user.end();iter++)
	{
		len = sizeof(iter.size());
		senddata(msg.iter->second,len);
	}
}
udp_server::~udp_server()
{
	close(sock);
}

