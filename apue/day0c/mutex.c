#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int a = 1;
int b = 1;
pthread_mutex_t mutex;

void * r1(void *arg)
{
	while ( 1 ) {
		pthread_mutex_lock(&mutex);
		a++;
		b++;
	
		if ( a != b ) {
			printf("%d!=%d\n", a, b);
			a = 0;
			b = 0;
		}
		pthread_mutex_unlock(&mutex);
	}
}

void * r2(void *arg)
{
	while ( 1 ) {
		pthread_mutex_lock(&mutex);
		a++;
		b++;
	
		if ( a != b ) {
			printf("%d!=%d\n", a, b);
			a = 0;
			b = 0;
		}
		pthread_mutex_unlock(&mutex);
	}
}

int main( void )
{
	int ret;
	pthread_t t1;
	pthread_t t2;
	
	pthread_mutex_init(&mutex, NULL);
	if ( (ret=pthread_create(&t1, NULL, r1, NULL)) != 0 ) 
		fprintf(stderr, "%s\n", strerror(ret)),exit(EXIT_FAILURE);
	if ( (ret=pthread_create(&t2, NULL, r2, NULL)) != 0 ) 
		fprintf(stderr, "%s\n", strerror(ret)),exit(EXIT_FAILURE);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);
}

