#pragma once
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#define PATHNAME "."
#define PROJ_ID 0
#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct msgbuf
{
	long mtype;
	char mtext[1024];
};

int creat_msg();
int get_msg();
int destroy_msg(int msgid);
int send_msg(int msgid,int who,char*msg);
int recv_msg(int msgid,int recvType,char out[]);
