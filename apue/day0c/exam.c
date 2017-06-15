#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void * run(void *data)
{
	int i;
	for (i=0; i<20; i++) {
		printf("B");
		fflush(stdout);
	}
}

int main( void )
{
	int i;
	int ret;
	pthread_t tid;
	
	if ( (ret=pthread_create(&tid, NULL, run, NULL)) != 0) {
		fprintf(stderr, "%s\n", strerror(ret));
		exit(EXIT_FAILURE);
	}
	
	for (i=0; i<20; i++) {
		printf("A");
		fflush(stdout);
	}
	
	pthread_join(tid, (void**)0);
	printf("\n");
}

