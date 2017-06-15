#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

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
	
	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");
	
	if ( pid == 0 ) {
		sleep(2);
		printf("I'm child!\n");
	}else {
		pid_t ret;
		if ( (ret=waitpid(pid, NULL, 0)) == -1)
			ERR_EXIT("waitpid");
		if ( ret == 0 )
			printf("no child exit!\n");
		printf("I'm parent!\n");
	}
	return 0;
}

