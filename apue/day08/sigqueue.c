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
		fprintf(stderr, "%s pid\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	
	union  sigval sv;
	sv.sival_int = 100;
	pid_t pid = atoi(argv[1]);
	
	sigqueue(pid, SIGINT, sv);
	return 0;
}

