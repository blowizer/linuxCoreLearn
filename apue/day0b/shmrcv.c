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
	stu_t *p;
	if ( (shmid=shmget(1234, 0, 0)) == -1)
		ERR_EXIT("shmget");
	
	if ( (p=(stu_t*)shmat(shmid, NULL, 0)) == (void *)-1)
		ERR_EXIT("shmat");
	
	printf("%s同学今年%d岁!\n", p->name, p->age);
	
	shmdt(p);
	shmctl(shmid, IPC_RMID, 0);
	return 0;
}

