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
	int fd;
	
	if ( (fd=fileno(stderr)) == -1)
		ERR_EXIT("fileno");
	
	printf("fd = %d\n", fd);

	return 0;
}

