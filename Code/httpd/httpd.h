#ifndef __HTTPD_H__
#define __HTTPD_H__
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
#define SIZE 1024*4

void *handler_request(void *arg);
int startup(const char*ip,int port);

void error_response(int sock,int err_code);
void handler_handler(int sock);

#endif
