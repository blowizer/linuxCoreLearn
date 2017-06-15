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

int gVal = 100;

int main( void ) {
	pid_t pid;
	
	if ( (pid=vfork()) == -1)
		ERR_EXIT("fork");

	if ( pid == 0 ) {
		gVal ++;
		printf("in child %d\n", gVal);
	} else {
		sleep(1);
		printf("in parent %d\n", gVal);
	}

	exit(EXIT_SUCCESS);
}

