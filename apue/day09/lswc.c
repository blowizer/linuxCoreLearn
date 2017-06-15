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
	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");
	
	if ( pid == 0 ) {
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		execlp("ls", "ls", NULL);
		fprintf(stderr, "execlp err:%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	close(fds[1]);
	dup2(fds[0], 0);
	close(fds[0]);
	execlp("wc", "wc", "-w", NULL);
	fprintf(stderr, "execlp err:%s\n", strerror(errno));
	exit(EXIT_FAILURE);
	
	return 0;
}

