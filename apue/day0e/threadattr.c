#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

pthread_attr_t attr;

#define ERR_EIXT(m) \
do { \
	fprintf(stderr, "[%s][%d]:%s\n", \
	__FILE__, __LINE__, strerror(m)); \
	exit(EXIT_FAILURE); \
}while(0)

void *run(void *arg)
{
	pthread_attr_init(&attr);
	int ret;
	int detachstate;
	pthread_attr_getdetachstate(&attr, &detachstate);
	if ( detachstate == PTHREAD_CREATE_DETACHED )
		printf("detachestat:PTHREAD_CREATE_DETACHED\n");
	else if ( detachstate == PTHREAD_CREATE_JOINABLE )
		printf("detachestat:PTHREAD_CREATE_JOINABLE\n");

	size_t stacksize;
	pthread_attr_getstacksize(&attr, &stacksize);
	printf("stacksize:%d\n", stacksize);

	size_t guardsize;
	pthread_attr_getguardsize(&attr, &guardsize);
	printf("guardsize:%d\n", guardsize);
	
	int contentionscope;
	pthread_attr_getscope(&attr, &contentionscope);
	if ( contentionscope == PTHREAD_SCOPE_SYSTEM )
		printf("contentionscop:PTHREAD_SCOPE_SYSTEM\n");
	else if ( contentionscope == PTHREAD_SCOPE_PROCESS )
		printf("contentionscop:PTHREAD_SCOPE_PROCESS\n");
	
	int policy;
	pthread_attr_getschedpolicy(&attr, &policy);
	if ( policy == SCHED_FIFO )
		printf("policy:SCHED_FIFO\n");
	else if ( policy == SCHED_RR)
		printf("policy:SCHED_RR\n");
	else if ( policy == SCHED_OTHER )
		printf("policy:SCHED_OTHER\n");

	int inheritsched;
	pthread_attr_getinheritsched(&attr, &inheritsched);
	if (inheritsched == PTHREAD_INHERIT_SCHED)
		printf("inheritsched:PTHREAD_INHERIT_SCHED\n");
	else if (inheritsched == PTHREAD_EXPLICIT_SCHED)
		printf("inheritsched:PTHREAD_EXPLICIT_SCHED\n");

	struct sched_param param;
	pthread_attr_getschedparam(&attr, &param);
	printf("priority:%d\n", param.sched_priority);
	
	int level;
	level = pthread_getconcurrency();
	printf("level=%d\n", level);

	pthread_attr_destroy(&attr);
}

int main( void )
{
	pthread_t tid;
	
	pthread_create(&tid, NULL, run, NULL);
	
	pthread_join(tid, NULL);
	
	return 0;
}

