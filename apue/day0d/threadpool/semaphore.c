#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>

sem_t sid;

void * f1(void *arg)
{
	while ( 1 ) {
		sem_wait(&sid);
		printf("唤醒!\n");
	}
}

void * f2(void *arg)
{
	while ( 1 ) {
		sem_post(&sid);
		sleep(1);
	}
}

int main( void )
{
	pthread_t tid1, tid2;
	sem_init(&sid, 0, 5);
	
	pthread_create(&tid1, NULL, f1, NULL);
	pthread_create(&tid2, NULL, f2, NULL);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	sem_destroy(&sid);
}

