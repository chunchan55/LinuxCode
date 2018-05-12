#include <stdio.h>
#include <stdlib.h>
#include "threadpool.h"


void *mytask(void *arg)
{
	printf("thread %#X working on %d\n", pthread_self(), (int)arg);
	sleep(1);
}

int main( void )
{
	threadpool_t pool;
	
	threadpool_init(&pool, 3);
	
	int i;
	for (i=0; i<10; i++) {
		threadpool_add_task(&pool, mytask, (void*)i);
	}
	
	//sleep(15);
	threadpool_destroy(&pool);
}

