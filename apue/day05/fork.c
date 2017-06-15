#include <unistd.h>
#include <fcntl.h>

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
	pid_t pid;
	
	printf("fork之前!pid=%d\n", getpid());
	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");
	
	if ( pid == 0 ) {
		printf("在子进程中pid=%d,ppid=%d\n",getpid(), getppid());
	} else if ( pid > 0 ) {
		sleep(1000);
		printf("在父进程中pid=%d, cid=%d\n",getpid(), pid);
	}
	
	return 0;
}

