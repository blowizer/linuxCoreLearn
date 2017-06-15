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
int semid;

int sem_create(key_t key)
{
	int semid;
	semid=semget(key, 1, IPC_CREAT|0666);
	if ( semid == -1)
		ERR_EXIT("semget");
	
	return semid;
}

void sem_setval(int semid, int val)
{
	union semun su;
	su.val = val;
	semctl(semid, 0, SETVAL, su);
}

void sem_p(int semid)
{
	struct sembuf sb = {0, -1, 0};
	if ( semop(semid, &sb, 1) == -1)
		ERR_EXIT("semop");
}


void sem_v(int semid)
{
	struct sembuf sb = {0, 1, 0};
	if ( semop(semid, &sb, 1) == -1)
		ERR_EXIT("semop");
}

#define PAUSE(m) rand()%(m)+1

void print(const char op )
{
	int i;
	int pause_time;
	srand(getpid());
	for (i=0; i<10; i++) {
		sem_p(semid);
		printf("%c", op);
		fflush(stdout);
		pause_time = PAUSE(3);
		sleep(pause_time);
		printf("%c", op);
		fflush(stdout);
		pause_time = PAUSE(2);
		sleep(pause_time);
		sem_v(semid);
	}
}

int main( void )
{
	pid_t pid;
	semid=sem_create(IPC_PRIVATE);
	sem_setval(semid, 0);

	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");

	if ( pid == 0 ) {
		print('X');
	} else if ( pid > 0 ) {
		sem_setval(semid, 1);
		print('O');
	}
}

