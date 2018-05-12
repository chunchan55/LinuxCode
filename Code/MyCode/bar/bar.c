#include<stdio.h>
#include<unistd.h>

int main()
{
	int i = 0;
	char bar[102] = {0};
	const char*labal = "|/-\\";//出现一个类似圈圈
	while(i<=100)
	{
		printf("\e[31m[%-100s][%d%%][%c]\r",bar,i,labal[i%4]);
		fflush(stdout);
		bar[i] = '#';
		i++;
		bar[i] = 0;
		usleep(100000);
	}
	printf("\e[0m \n");
	return 0;
}
