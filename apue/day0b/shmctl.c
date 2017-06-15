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

int main( void )
{
	int shmid;
	struct shmid_ds buf;

	if ( (shmid=shmget(1234, 0, 0)) == -1)
		ERR_EXIT("shmget");
	if ( shmctl(shmid, IPC_STAT,  &buf) == -1)
		ERR_EXIT("shmctl");
	
	printf("mode:%o\n", buf.shm_perm.mode);
	printf("attach:%d\n", buf.shm_nattch);
	printf("uid:%d\n", buf.shm_cpid);
	printf("size:%d\n", buf.shm_segsz);
	return 0;
}

