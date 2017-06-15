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
	int fd;
	if ( (fd = open("test.txt", O_RDWR)) == -1)
		ERR_EXIT("open");
	ftruncate(fd, 1024);
	write(fd, "hehe", 4);
	
	close(fd);
	return 0;
}

