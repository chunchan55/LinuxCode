#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t lock;
int count = 1000;
void* Count(void*arg )
{
	(void)arg;
	int i = 0;
	while(1)
	{
		if(count>0)
		{	
			usleep(123456);
			--count;
			printf("count=%d\n",count);
		}
		else
		{
			break;
		}
	}
}
int main()
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_mutex_init(&lock,NULL);

	pthread_create(&tid1,NULL,Count,NULL);
	pthread_create(&tid2,NULL,Count,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	pthread_mutex_destroy(&lock);

}
