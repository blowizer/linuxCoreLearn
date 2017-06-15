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

void handler(int s) {
	printf("time out!\n");
	exit(EXIT_SUCCESS);
}

int main( void ) {
	int ret;
	char buf[1024] = {};
	
	signal(SIGALRM, handler);
	
	alarm(5);
	printf("input: ");
	fflush(stdout);
	if ( (ret=read(0, buf, 1024)) < 0 ) {
		printf("unkown err!\n");
	}
	alarm(0);
	if ( ret > 0 )
		printf("info:%s\n", buf);

	return 0;
}

