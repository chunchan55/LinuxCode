#include "threadpool.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void threadpool_init(threadpool_t *pool, int threads)
{
	condition_init(&pool->ready);
	pool->first       = NULL;
	pool->last        = NULL;
	pool->counter     = 0;
	pool->idle        = 0;
	pool->max_threads = threads;
	pool->quit        = 0;
}

void *route(void *arg)
{
	threadpool_t *pool = (threadpool_t*)arg;
	int timeout = 0;
	
	while ( 1 ) {
		condition_lock(&pool->ready);
		timeout = 0;	
		pool->idle++;
		
		// 等待任务队列有任务到来或线程销毁通知
		while ( pool->first == NULL && pool->quit == 0 ) {
			//condition_wait(&pool->ready);
			struct timespec ts;
			clock_gettime(CLOCK_REALTIME, &ts);
			ts.tv_sec += 2;
			int ret = condition_timedwait(&pool->ready, &ts);
			if ( ret == ETIMEDOUT ) {
				printf("%#X thread timeout!\n", (int)pthread_self());
				timeout = 1;
				break;
			}
		}
		// 等待到条件，空闲线程数量减少
		pool->idle--;
	
		if ( pool->first != NULL ) {
			// 从队头取任务进行执行
			task_t *t = pool->first;
			pool->first = t->next;
			// 防止run函数执行的时间太长
			condition_unlock(&pool->ready);
			t->run(t->arg);
			condition_lock(&pool->ready);
			free(t);
		}
	
		// 等待到线程池销毁通知,并且任务都执行完毕
		if ( pool->quit == 1 && pool->first == NULL ) {
			pool->counter--;
			if ( pool->counter == 0 )
				condition_signal(&pool->ready);
			// 跳出循环之前，要记得解锁
			condition_unlock(&pool->ready);
			break;
		}
	
		// 超时处理
		if ( timeout == 1 && pool->first == NULL ) {
			pool->counter--;
			condition_unlock(&pool->ready);
			break;
		}
		
		condition_unlock(&pool->ready);
	}
}

void threadpool_add_task(threadpool_t *pool, void *(*run)(void*), void *arg)
{
	task_t *newtask = malloc(sizeof(task_t));
	newtask->run = run;
	newtask->arg = arg;
	newtask->next = NULL;
	
	condition_lock(&pool->ready);
	if ( pool->first == NULL )
		pool->first = newtask;
	else
		pool->last->next = newtask;
	pool->last = newtask;
	
	if ( pool->idle > 0 ) {
		condition_signal(&pool->ready);
	} else if ( pool->counter < pool->max_threads ) {
		pthread_t tid;
		pthread_create(&tid, NULL, route, pool);
		pool->counter++;
	}

	condition_unlock(&pool->ready);
}

void threadpool_destroy(threadpool_t *pool)
{
	if ( pool->quit == 1 )
		return;
	
	condition_lock(&pool->ready);
	pool->quit = 1;
	if ( pool->counter > 0 ) {
		if ( pool->idle > 0 ) 
			condition_broadcast(&pool->ready);
		// 如果发通知时有线程在工作，通知就丢失
		// 所以需要最后一个线程销毁时，给这个地方发送通知
		while ( pool->counter > 0 )
			condition_wait(&pool->ready);
	}
	
	condition_unlock(&pool->ready);
	condition_destroy(&pool->ready);
}

