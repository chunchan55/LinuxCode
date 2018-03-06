#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/wait.h>
#include<string.h>
int main()
{
	char result_buf[1024],command[1024];
	int rc = 0;//用于接收命令的返回值
	FILE*fp;
	//将要执行的命令写入buf
	snprintf(command,sizeof(command),"cat test");
	//执行预先设定的命令，并读出该命令的标准输出
	fp = popen(command,"r");//读
	if(fp == NULL)
	{
		perror("popen");
		exit(1);
	}
	while(fgets(result_buf,sizeof(result_buf),fp)!=NULL)
	{
		if('\n' == result_buf[strlen(result_buf)-1])
		{
			result_buf[strlen(result_buf)-1] = '\0';
		}
		printf("命令[%s] 输出[%s] \r\n",command,result_buf);
	}

	//命令执行完关闭管道和文件指针
	rc = pclose(fp);
	if(-1 == rc)
	{
		perror("pclose");
		exit(1);
	}
	else
	{
		printf("命令[%s] 子进程结束状态[%d] 命令返回值[%d] \r\n",command,rc,WEXITSTATUS(rc));
	}
	return 0;
}
