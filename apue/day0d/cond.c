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

pthread_cond_t cond;
pthread_mutex_t mutex;

void *run1(void* arg)
{
	while ( 1 ) {
		pthread_cond_wait(&cond, &mutex);
		printf("激活!\n");
	}
}

void *run2(void* arg)
{
	while ( 1 ) {
		pthread_cond_signal(&cond);		
		sleep(1);
	}
}

int main()
{
	int ret;
	pthread_t tid1;
	pthread_t tid2;

	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);
	ret=pthread_create(&tid1, NULL, run1, NULL);
	if ( ret != 0 ) ERR_EIXT(ret);
	ret=pthread_create(&tid2, NULL, run2, NULL);
	if ( ret != 0 ) ERR_EIXT(ret);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
	
	return 0;
}

