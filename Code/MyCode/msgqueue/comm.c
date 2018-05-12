#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include"comm.h"

int CommonMsg(int flag)
{
	key_t key = ftok(PATHNAME,PROJ_ID);
	if(key < 0)
	{
		perror("ftok");
		return 164;
	}
	int msgid = msgget(key,flag);
	if(msgid < 0 )
	{
		perror("msgget");
		return -2;
	}
	return msgid;
}
int creat_msg()
{
	return CommonMsg(IPC_CREAT|IPC_EXCL|0666);
}
int get_msg()
{
	return CommonMsg(IPC_CREAT);
}

int destroy_msg(int msgid)
{
	int ret = msgctl(msgid,IPC_RMID,NULL);
	if(ret < 0)
	{		perror("msgctl");
		return -1;
	}
	return 0;
}
int send_msg(int msgid,int who,char*msg)
{
	struct msgbuf buf;//按照格式必须定义一个结构体
	buf.mtype = who;
	strcpy(buf.mtext,msg);//把传过来的字符串拷贝过去
	if(msgsnd(msgid,(void*)&buf,sizeof(buf.mtext),0) < 0)//
	{
		perror("msgsnd");
		return -1;
	}
	return 0;
}
int recv_msg(int msgid,int recvType,char out[])
{

	struct msgbuf buf;//按照格式必须定义一个结构体
	if(msgrcv(msgid,(void*)&buf,sizeof(buf.mtext),recvType,0) < 0)//
	{
		perror("msgrcv");
		return -1;
	}
	strcpy(out,buf.mtext);//再把消息队列里面的内容写到数组
	return 0;
}
