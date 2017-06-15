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

void handler(int s) {
	printf("recv sig %d\n", s);
}

int main( void )
{
	pid_t pid;
	
	if ( signal(SIGUSR1, handler) == SIG_ERR)
		ERR_EXIT("signal");
	
	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");
	
	if ( pid == 0 ) {
		kill(getppid(), SIGUSR1);
		exit(EXIT_SUCCESS);
	}
	
	int n = 5;
	do {
		n=sleep(n);
	} while ( n > 0 );
	
	while ( 1 )  {
		printf(".");
		fflush(stdout);
		sleep(1);
	}

	return 0;
}

