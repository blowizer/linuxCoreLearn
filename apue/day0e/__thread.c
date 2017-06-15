#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

__thread int g_data;

void *run1(void *arg)
{
	g_data = 20;
	printf("run1=%d\n", g_data);
	sleep(2);
	printf("run1=%d\n", g_data);
}

void *run2(void *arg)
{
	g_data = 10;
	printf("run2=%d\n", g_data);
	sleep(2);
	printf("run2=%d\n", g_data);
}

int main( void )
{
	pthread_t tid1;
	pthread_t tid2;
	
	pthread_create(&tid1, NULL, run1, NULL);
	pthread_create(&tid2, NULL, run2, NULL);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}

