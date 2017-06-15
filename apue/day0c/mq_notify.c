#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

typedef struct stu{
	char name[32];
	int age;
}stu_t;

mqd_t mqd;
struct mq_attr attr;
struct sigevent event;

void handler(int sig) {
	mq_notify(mqd, &event);
	stu_t s;
	int len = attr.mq_msgsize;
	unsigned prio;
	if ( mq_receive(mqd, (char*)&s, len, &prio) == -1)
		ERR_EXIT("mq_receive");
	
	printf("age=%d, name=%s\n", s.age, s.name);
} 

int main( int argc, char *argv[] )
{
	mqd=mq_open("/abc", O_RDWR);
	if ( mqd == (mqd_t)-1)
		ERR_EXIT("mq_open");

	struct sigaction act;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if ( sigaction(SIGUSR1, &act, NULL) == -1)
		ERR_EXIT("sigaction");
	
    if ( mq_getattr(mqd, &attr) == -1) 
        ERR_EXIT("mq_getattr");
	
	event.sigev_notify = SIGEV_SIGNAL;
	event.sigev_signo = SIGUSR1;
	mq_notify(mqd, &event);
	
	for( ; ; )
		pause();
	
	mq_close(mqd);
	return 0;
}

