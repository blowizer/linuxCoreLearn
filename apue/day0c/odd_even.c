#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

#define ERR_EIXT(m) \
do { \
	fprintf(stderr, "[%s][%d]:%s\n", \
	__FILE__, __LINE__, strerror(m)); \
	exit(EXIT_FAILURE); \
}while(0)

pthread_mutex_t mutex;

void handler(void *data)
{
	printf("线程退出后调用我!\n");
	pthread_mutex_unlock(&mutex);
}

void * odd(void *arg)
{
	int i;
	
	for (i=1; ; i+=2) {
		pthread_cleanup_push(handler, NULL);
		pthread_mutex_lock(&mutex);
		printf("odd number : %d\n", i);
		pthread_mutex_unlock(&mutex);
		pthread_cleanup_pop(0);
	}
}

void * even(void *arg)
{
	int i;
	
	for (i=0; ; i+=2) {
		pthread_cleanup_push(handler, NULL);
		pthread_mutex_lock(&mutex);
		printf("even number : %d\n", i);
		pthread_mutex_unlock(&mutex);
		pthread_cleanup_pop(0);
	}
}

int main( void )
{
	int ret;
	pthread_t tid1;
	pthread_t tid2;
	
	pthread_mutex_init(&mutex, NULL);
	if ( (ret=pthread_create(&tid1, NULL, odd, NULL)) != 0)
		ERR_EIXT(ret);
	if ( (ret=pthread_create(&tid2, NULL, even, NULL)) != 0)
		ERR_EIXT(ret);
	
	sleep(1);
	pthread_cancel(tid1);
	sleep(1);
	pthread_cancel(tid2);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_mutex_destroy(&mutex);

	return 0;
}

