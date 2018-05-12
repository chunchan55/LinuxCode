#include"udp_server.h"

using namespace std;

static void usage(std::string proc)
{
	cout<<"usage: "<<proc<<" [local_ip] [local_port]"<<endl;
}
static void *runrecv(void*arg)
{
	udp_server *svrp = (udp_server*)arg;
	std::string msg;
	for(;;)
	{
		svrp->recvdata(msg);
		cout<<"client: "<<msg<<endl;
	}
}

static void *runsend(void*arg)
{
	udp_server *svrp = (udp_server*)arg;
	for(;;)
	{
		svrp->brocast();//guang bo
	}
}
int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}
	int port = atoi(argv[2]);
	udp_server svr(argv[1],port);
	svr.initserver();
	pthread_t recv_thread,send_thread;
	pthread_create(&recv_thread,NULL,runrecv,(void*)svr);
	pthread_create(&send_thread,NULL,runsend,(void*)svr);

	pthread_join(recv_thread,NULL);
	pthread_join(send_thread,NULL);
	return 0;
}
