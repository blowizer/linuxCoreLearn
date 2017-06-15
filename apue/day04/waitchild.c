#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

void handler(int s)
{
	waitpid(-1, NULL, WNOHANG);
}


int main( void )
{
	int i;
	pid_t pid;
	struct sigaction sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if ( sigaction(SIGCHLD, &sa, NULL) == -1)
		ERR_EXIT("sigaction");

	if ( (pid=fork()) == -1 )
		ERR_EXIT("fork");	
	
	if ( pid == 0 ) {
		for (i=0; i<5; i++) {
			printf(".");
			fflush(stdout);
			sleep(1);
		}
		exit(EXIT_SUCCESS);
	}
	
	for (; ; ) {
		printf("$");
		fflush(stdout);
		sleep(1);
	}

	return 0;
}

