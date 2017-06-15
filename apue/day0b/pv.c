
#include <unistd.h>
#include <fcntl.h>
#include <sys/type.h>
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

int sem_creat( key_t key )
{

	if((semid=semget(1234,O_CREAT|0666)==-1))
		ERR_EXIT("semget");
	
}
void  sem_open(int semid)
{
}
int sem_p(int semid)
{
		
}
int sem_v(int semid)
{

}
int main(void)
{
	pit_t pid;
	
}
