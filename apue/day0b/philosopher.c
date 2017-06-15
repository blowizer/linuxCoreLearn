#include <unistd.h>
#include <fcntl.h>
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
    int  val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
};

int semid;

void wait_for_2fork(int no)
{
	int left = no;
	int right = (no+1) % 5;
	struct sembuf sb[2] = {{left, -1, 0}, {right, -1, 0}};
	semop(semid, sb, 2);
}
void wait_for_left(int no)
{
	int left = no;
	struct sembuf sb = {left, -1, 0};
	semop(semid, &sb, 1);
}
void wait_for_right(int no)
{
	int right = (no+1) % 5;
	struct sembuf sb = {right, -1, 0};
	semop(semid, &sb, 1);
}

void free_2fork(int no)
{
	int left = no;
	int right = (no+1) % 5;
	struct sembuf sb[2] = {{left, 1, 0}, {right, 1, 0}};
	semop(semid, sb, 2);
}

void free_left(int no)
{
	int left = no;
	struct sembuf sb = {left, 1, 0};
	semop(semid, &sb, 1);
}

void free_right(int no)
{
	int right = (no+1) % 5;
	struct sembuf sb = {right, 1, 0};
	semop(semid, &sb, 1);
}

void philosopher(int no)
{
	srand(getpid());
	for (; ; ) {
		printf("%d is thinking...\n", no);
		sleep(rand()%5+1);
		printf("%d is hungry\n", no);
		//wait_for_2fork(no);
		wait_for_left(no);
		sleep(rand()%5+1);
		wait_for_right(no);
		printf("%d is eating\n", no);
		sleep(rand()%3+1);
		//free_2fork(no);
		free_left(no);
		sleep(rand()%5+1);
		free_right(no);
	}
}

int main( void )
{
	int i;
	int no = 0;
	pid_t pid;

	semid = semget(IPC_PRIVATE, 5, IPC_CREAT|0666);
	if ( semid == -1)
		ERR_EXIT("semget");

	union semun su;
	su.val = 1;
	for (i=0; i<5; i++)
		semctl(semid, i, SETVAL, su);

	for (i=1; i<5; i++) {
		if ( (pid=fork()) == -1)
			ERR_EXIT("fork");
		if ( pid == 0) {
			no = i;
			break;
		}
	}
	
	philosopher(no);
	
	return 0;
}

