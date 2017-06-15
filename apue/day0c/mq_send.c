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
	if ( argc != 2 ) {
		fprintf(stderr, "usage:%s prio\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	mqd_t mqd;
	mqd=mq_open("/abc", O_RDWR);
	if ( mqd == (mqd_t)-1)
		ERR_EXIT("mq_open");
	
	stu_t s;
	strcpy(s.name, "Jock");
	s.age = 20;
	
	unsigned prio = atoi(argv[1]);
	if ( mq_send(mqd, (char*)&s, sizeof(s), prio) == -1)
		ERR_EXIT("mq_send");
	
	mq_close(mqd);
	return 0;
}

