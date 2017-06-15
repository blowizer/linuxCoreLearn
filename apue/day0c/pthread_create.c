#include <unistd.h>
#include <pthread.h>
#include <sched.h>

#include <stdio.h>
#include <stdlib.h>

void *run(void *data ){
	//while ( 1 ) {
		printf("%d!\n", (int)data);
	//	sched_yield();
	//}
}

int main( void )
{
	pthread_t tid;
	if ( pthread_create(&tid, NULL, run, (void*)tid) != 0 ) {
		printf("create thread err!\n");
		exit(EXIT_SUCCESS);
	}
	
	//主线程退出，新线程也跟着推出
	//解决之道
	//sleep(1);
	pthread_join(tid, (void**)0);
/*	
	while ( 1 ) {
		printf("我是主线程!\n");
		sched_yield();
	}
*/
}

