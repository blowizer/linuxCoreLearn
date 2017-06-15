#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

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
	if ( mkfifo("my.p", 0666) == -1)
		ERR_EXIT("mkfifo");
	return 0;
}

