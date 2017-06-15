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
	int fd[2];
	int flags;
	int counter = 0;

	if ( pipe(fd) == -1)
		ERR_EXIT("pipe");

	flags = fcntl(fd[1], F_SETFL, 0);
	fcntl(fd[1], F_SETFL, flags|O_NONBLOCK);
	
	while ( 1 ) {
		if ( write(fd[1], "X", 1) == -1)
			break;
		counter++;
	}

	printf("counter=%d\n", counter);
	
	return 0;
}

