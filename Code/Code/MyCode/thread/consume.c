#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
pthread_cond_t g_cond;//创建信号量
pthread_mutex_t g_mutex;//创建互斥锁


//创建一个交易场所 链表 带头结点
typedef struct Node
{
	int data;
	struct Node* next;
}Node;

Node* CreatNode(int value)
{
	Node*newNode = (Node*)malloc(sizeof(Node));
	newNode->data = value;
	newNode->next = NULL;
	return newNode;
}
void InitList(Node**head)
{
	*head = CreatNode(-1);
}
void Push(Node*head,int value)//头插
{
	Node* newNode = CreatNode(value);//创建一个结点
	Node*cur = head->next;
	head->next = newNode;
	newNode->next = cur;
}
void Pop(Node*head)//头删
{
	Node*del = head->next;
	head->next = del->next;
	free(del);
}

//两个角色 就是创建两个线程

Node* head;
void* Product(void*arg)
{
	//获取锁，然后发数据，发送信号告诉进程条件成熟
	//释放锁 休眠
	(void)arg;
	int count = 0;
	while(1)
	{
		pthread_mutex_lock(&g_mutex);
		Push(head,++count);
		printf("product %d\n",count);
		pthread_cond_signal(&g_cond);
	//	printf("传球\n");
		pthread_mutex_unlock(&g_mutex);
		usleep(678123);
	}
}

void* Consumer(void*arg)
{
	//获取锁 发现条件不成熟 就循环等待，直到conduct完，然后继续执行，释放锁，pop
	(void)arg;
	while(1)
	{
		pthread_mutex_lock(&g_mutex);
		while(head->next == NULL)
		{
			//printf("投篮\n");
			pthread_cond_wait(&g_cond,&g_mutex);//循环等待，直到收到信号
		}
		pthread_mutex_unlock(&g_mutex);//等完后就释放锁
		printf("consumer %d\n",head->next->data);
		Pop(head);
		usleep(123456);
	}
}

int main()
{
	pthread_t tid1,tid2;
	InitList(&head);//初始化单链表
	pthread_mutex_init(&g_mutex,NULL);
	pthread_cond_init(&g_cond,NULL);

	pthread_create(&tid1,NULL,Consumer,NULL);
	pthread_create(&tid2,NULL,Product,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	pthread_mutex_destroy(&g_mutex);
	pthread_cond_destroy(&g_cond);

}
