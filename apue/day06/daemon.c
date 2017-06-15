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

int setup_daemon( void ) {
	pid_t pid;
	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");
	
	if ( pid > 0 )
		exit(EXIT_SUCCESS);
	
	
	setsid();
	chdir("/");
	int i;
	
	for (i=0; i<100; i++)
		close(i);
	while ( 1 );
}

int main( void )
{
	setup_daemon();
	return 0;
}

