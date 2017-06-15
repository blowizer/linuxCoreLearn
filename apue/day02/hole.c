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
	
	if ( (fd=open("hole.txt", O_RDWR|O_TRUNC|O_CREAT|O_EXCL)) == -1)
		ERR_EXIT("open");
	
	lseek(fd, 2*128, SEEK_END);
	write(fd, "lilei", 5);
	
	close(fd);
	return 0;
}

