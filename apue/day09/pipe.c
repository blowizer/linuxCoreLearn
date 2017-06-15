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
	int fds[2];
	pid_t pid;
	if ( pipe(fds) == -1)
		ERR_EXIT("pipe");
	
	if ( (pid=fork()) == -1 )
		ERR_EXIT("fork");
	
	if ( pid == 0 ) {
		close(fds[0]);
		write(fds[1], "hello", 6);
		close(fds[1]);
		exit(EXIT_SUCCESS);
	}
	
	char buf[1024] = {};
	close(fds[1]);
	read(fds[0], buf, 1024);
	close(fds[0]);
	printf("buf=%s\n", buf);
	
	return 0;
}
