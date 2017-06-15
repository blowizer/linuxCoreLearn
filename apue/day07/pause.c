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
	printf("recv sig %d\n", s);
}

int main( void )
{
	if ( signal(SIGINT, handler) == SIG_ERR)
		ERR_EXIT("signal");

	for ( ; ; ) {
		pause();
		printf("pause return!\n");
	}

	return 0;
} 

