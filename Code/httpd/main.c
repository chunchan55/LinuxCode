#include<pthread.h>
#include"httpd.h"

static void usage(const char*proc)
{
	printf("usage:\n\t%s [local_ip] [local_port]\n\n",proc);
}
int main(int argc,const char*argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}
	int listen_sock = startup(argv[1],atoi(argv[2]));
	while(1)
	{
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		int rw_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
		if(rw_sock < 0)
		{
			perror("accept");
			continue;
		}
		pthread_t id;
		pthread_create(&id,NULL,handler_request,(void*)rw_sock);
		pthread_detach(id);//线程分离，读写锁
	}
//	close(listen_sock);
	return 0;
}
