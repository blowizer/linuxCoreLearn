#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

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
	//signal(SIGCHLD, SIG_IGN); 让子进程不会进入僵尸状态
	
	pid_t pid;
	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");
	
	if ( pid == 0 ) {
		printf("我是子进程!\n");
		exit(EXIT_SUCCESS);
	} else {
		sleep(10000);
		exit(EXIT_SUCCESS);
	}
	return 0;
}

