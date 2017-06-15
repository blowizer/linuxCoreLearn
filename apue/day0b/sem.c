#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

union semun {
	int              val;
	struct semid_ds *buf;
};

int sem_create(key_t key)
{
	int semid;
	semid=semget(key, 1, IPC_CREAT|IPC_EXCL|0666);
	if ( semid == -1)
		ERR_EXIT("semget");
	
	return semid;
}

int sem_open(key_t key)
{
	int semid;
	semid=semget(key, 0, 0);
	if ( semid == -1)
		ERR_EXIT("semget");
	
	return semid;
}

int sem_d(key_t key)
{
	int semid;
	semid=semget(key, 0, 0);
	if ( semid == -1)
		ERR_EXIT("semget");
	
	semctl(semid, 0, IPC_RMID);
}

int sem_setval(int semid, int val)
{
	int ret;
	union semun un;
	un.val = val;
	ret = semctl(semid, 0, SETVAL, un);
	return ret;
}

int sem_getval(int semid)
{
	int ret;
	ret=semctl(semid, 0, GETVAL, 0);
	
	return ret;
}

int sem_p(int semid)
{
	int ret;
	struct sembuf sb = {0, -1, 0};
	ret=semop(semid, &sb, 1);
	return ret;
}

int sem_v(int semid)
{
	int ret;
	struct sembuf sb = {0, 1, 0};
	ret=semop(semid, &sb, 1);
	return ret;
}

int main( void )
{
	int semid;
	semid=sem_create(1234);
	sem_setval(semid, 5);
	printf("val=%d\n", sem_getval(semid));
	sem_p(semid);	
	printf("val=%d\n", sem_getval(semid));
	sem_p(semid);	
	printf("val=%d\n", sem_getval(semid));
	sem_v(semid);	
	printf("val=%d\n", sem_getval(semid));
	//sem_d(1234);
	return 0;
}

