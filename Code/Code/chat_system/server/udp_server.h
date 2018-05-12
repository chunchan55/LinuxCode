#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

#include<iostream>
#include<sys/types.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/sendfile.h> 
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<errno.h>
#include<string>
#include<map>


#include"data_pool.h"
class udp_server
{
	public:
		udp_server(const std::string _ip,const int &_port)
		~udp_server();
		const int &sendData(const std::string&instring,struct sockaddr_in &remote,socklen_t &len)
		const int &recvData(std::string&outstring)
		void adduser(const struct sockaddr_in &remote)
		bool initserver()
		int brocast()
	private:
		std::string ip;
		int port;
		int sock;
		std::map<int,struct sockaddr_in> online_user;
		data_pool pool;
};



#endif
