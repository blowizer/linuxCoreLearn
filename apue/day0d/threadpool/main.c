#include <stdio.h>
#include <malloc.h>

#include "threadpool.h"

void * mytask( void * arg)
{
	printf("%#X working on %d\n", pthread_self(), *(int*)arg);
	sleep(1);
	free(arg);
	return NULL;
}

int main( void )
{
	threadpool_t pool;
	
	threadpool_init(&pool, 3);

	int i;
	
	for (i=0; i<5; i++) {
		int *arg = (int*)malloc(sizeof(int));
		*arg = i;
		threadpool_add_task(&pool, mytask, arg);
	}

	//sleep(15);
	
	threadpool_destroy(&pool);
}

