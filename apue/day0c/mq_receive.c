#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

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

int main( int argc, char *argv[] )
{
	mqd_t mqd;
	mqd=mq_open("/abc", O_RDWR);
	if ( mqd == (mqd_t)-1)
		ERR_EXIT("mq_open");
	
	struct mq_attr attr;
    if ( mq_getattr(mqd, &attr) == -1) 
        ERR_EXIT("mq_getattr");
	int len = attr.mq_msgsize;
	
	stu_t s;
	unsigned prio;
	if ( mq_receive(mqd, (char*)&s, len, &prio) == -1)
		ERR_EXIT("mq_receive");
	
	printf("age=%d, name=%s\n", s.age, s.name);
	
	mq_close(mqd);
	return 0;
}

