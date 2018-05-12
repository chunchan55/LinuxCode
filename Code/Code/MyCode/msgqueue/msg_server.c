#include"comm.h"

int main()
{
	int msgid = creat_msg();
	char buf[1024];
	while(1)
	{
		buf[0] = 0;
		recv_msg(msgid,CLIENT_TYPE,buf);
		printf("client# %s\n",buf);

		printf("please enter# ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf));//标准输入读
		if(s > 0)
		{
			buf[s-1] = 0;
			send_msg(msgid,SERVER_TYPE,buf);
			printf("send done,wait recv...\n");
		}
		
	}
	destroy_msg(msgid);
	return 0;

}
