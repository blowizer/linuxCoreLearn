#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

typedef struct stu
{
	char name[20];
	int age;
}stu_t;

int main( void )
{
	int shmid;
	if ( (shmid=shmget(1234, sizeof(stu_t), IPC_CREAT|0666)) == -1)
		ERR_EXIT("shmget");
	return 0;
}

