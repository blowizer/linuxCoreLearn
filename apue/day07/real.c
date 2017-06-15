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
	printf("recv a sig=%d\n", s);
	sleep(3);
}

int main( void ) {
	__sighandler_t oldhandler;
	if ( (oldhandler=signal(SIGRTMIN, handler)) == SIG_ERR )
		ERR_EXIT("signal");
	
	while ( 1 );

	return 0;
}

