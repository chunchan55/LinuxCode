#include"comm.h"

int main()
{
	int msgid = get_msg();
	char buf[1024];
	while(1)
	{
		buf[0] = 0;
		printf("pleale enter# ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf));//从标准输入读取数据
		if(s > 0)
		{	
			buf[s-1] = 0;//留一个\0
			send_msg(msgid,CLIENT_TYPE,buf);
			printf("send done,wait recv...\n");
		}
		recv_msg(msgid,SERVER_TYPE,buf);
		printf("server# %s\n",buf);
	}
	return 0;
}
