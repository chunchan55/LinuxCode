#include<stdio.h>
#include<unistd.h>

int main()
{
	const char*label = "|/-\\";
	char buf[101] = {0};
	int i = 0;
	for(;i<50;++i)
	{
		buf[i] = '#';
		printf("[%d%%][%c][%s]\r",i*2,label[i%4],buf);
		fflush(stdout);
		usleep(10000);
	}
}
