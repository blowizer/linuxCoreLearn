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

int main( int argc, char *argv[])
{
	if ( argc != 2 ) {
		fprintf(stderr, "usage : %s pid\n", argv[0]);
		exit(EXIT_SUCCESS); 
	}
	
	pid_t pid = atoi(argv[1]);
	union sigval sv;
	
	sigqueue(pid, SIGINT, sv);
	sigqueue(pid, SIGINT, sv);
	sigqueue(pid, SIGINT, sv);
	sigqueue(pid, SIGRTMIN, sv);
	sigqueue(pid, SIGRTMIN, sv);
	sigqueue(pid, SIGRTMIN, sv);

	sleep(1);
	kill(pid, SIGUSR1);

	return 0;

}

