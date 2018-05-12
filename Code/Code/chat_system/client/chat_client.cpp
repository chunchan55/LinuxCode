#include"udp_client.h"

using namespace std;

static void usage(std::string proc)
{
	cout<<"usage: "<<proc<<" [remote_ip] [remote_port]"<<endl;
}

int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}
	int port = atoi(argv[2]);
	udp_client cli(argv[1],port);
	cli.initclient();
	while(1)
	{
		std::string msg = "hello word";
		senddata(msg);
		sleep(2);
		msg = "";
		recvdata(msg);
	}
	return 0;
}
