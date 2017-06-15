
#include <unistd.h>
#include <fcntl.h>

#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/msg.h>
#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

typedef struct stu{
		int age;
		char name[20];

	}stu_t;
int main( void )

{
	int shmid;
	stu_t *p;
	
	if((shmid=shmget(1234,O_CREAT|O_EXCL,0666))==-1)
		ERR_EXIT("shmget");
	
	if((p=(stu_t *)shmat(shmid,NULL,0))==(void *)-1)
		ERR_EXIT("shmat");
	//printf("%s 同学今年 %d!\n",p->name,p->age);
	strcpy(p->name,"wgj");
	p->age=23;
	printf("%s 同学今年 %d!\n",p->name,p->age);
	sleep(10);
	shmdt(p);
	shmctl(shmid,IPC_RMID,0);
	
	return 0;
}
