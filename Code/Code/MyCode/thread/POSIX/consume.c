#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define QueueMaxSize 1024
sem_t g_lock;
sem_t g_data_num;
sem_t g_blank_num;
//1.创建一个交易场所 队列，用数组实现
typedef struct QueueNode
{
	int data[QueueMaxSize];
	int head;
	int tail;
	size_t size;
}Queue;

Queue*q;//对象
void InitQueue(Queue*q)
{
	printf("hai\n");
	q->head = 0;
	q->tail = 0;
	q->size = 0;//初始化
}
void Push(Queue*q,int value)
{
	printf("haha\n");
	if(q->size >= QueueMaxSize)
	{
		return;
	}
	q->data[q->tail++] = value;
	q->tail %= QueueMaxSize;
	++q->size;
}
void Pop(Queue*q,int* value)
{
	printf("hahaha\n");
	if(q->size == 0)
	{
		return;
	}
	*value = q->data[q->head++];
	q->head %= QueueMaxSize;
	--q->size;
}

void*product(void*arg)
{
	(void)arg;
	int value = 0;
	while(1)
	{
		//printf("frdhka\n");
		sem_wait(&g_blank_num);//申请空白资源，才能插入
		sem_wait(&g_lock);
		Push(q,++value);
		printf("product %d\\n",value);
		sem_post(&g_lock);
		sem_wait(&g_data_num);//数据资源加1
		usleep(678123);
	}
}

void*consumer(void*arg)
{
	(void)arg;
	while(1)
	{
		sem_wait(&g_data_num);//申请数据资源，才能删除
		int value = 0;
		sem_wait(&g_lock);
		Pop(q,&value);
		printf("consumer %d\n",q->data[value]);
		sem_post(&g_lock);
		sem_wait(&g_blank_num);//数据资源加1
		usleep(123456);
	}
}

int main()
{
	printf("sdaer\n");
	InitQueue(q);
	pthread_t tid1,tid2;
	printf("_t\n");
	sem_init(&g_lock,0,1);
	sem_init(&g_data_num,0,0);
	sem_init(&g_blank_num,0,QueueMaxSize);
	printf("nihao\n");
	pthread_create(&tid1,NULL,consumer,NULL);
	printf("hehe\n");
	pthread_create(&tid2,NULL,product,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	sem_destroy(&g_lock);
	sem_destroy(&g_data_num);
	sem_destroy(&g_blank_num);
}
