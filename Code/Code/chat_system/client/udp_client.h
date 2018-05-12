#ifndef _UDP_CLIENT_H_
#define _UDP_CLIENT_H_

#include<iostream>
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
class udp_client
{
	public:
		udp_server(const std::string _ip,const int &_port);
		~udp_client();
		bool initclient();
		const int &recvData(std::string& outstring);
		const int &sendData(const std::string& instring);
	private:
		std::string ip;
		int port;
		int sock;
};









#endif
