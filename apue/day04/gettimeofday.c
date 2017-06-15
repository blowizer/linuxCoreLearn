#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

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
	struct timeval tv;
	
	if ( gettimeofday(&tv, NULL) == -1)
		ERR_EXIT("gettimeofday");
	printf("sec:%d\n", tv.tv_sec);
	printf("msec:%d\n", tv.tv_usec);
	return 0;
}

