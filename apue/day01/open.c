#include <fcntl.h>
#include <unistd.h>

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
	
	if ( (fd=open("naichameimei.log", O_RDONLY)) == -1)
		ERR_EXIT("open");
	else
		printf("open successful!\n");
	
	if ( close(fd) == -1)
		ERR_EXIT("close");

	return 0;
}

