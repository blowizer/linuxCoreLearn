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
	
	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");
	
	if ( pid == 0 ) {
		while ( 1 ) {
			//usleep(100000);
			printf(".");
			fflush(stdout);
		}
	} else {
		while ( 1 ) {
			//usleep(100000);
			printf("X");
			fflush(stdout);
		}
	}

	return 0;
}

