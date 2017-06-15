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

#define MAXLINE 2

int main( int argc, char *argv[] )
{
	int fd;
	int ret;
	char buf[MAXLINE+1];

	if ( argc != 2 ) {
		fprintf(stderr, "usage : %s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(buf, 0x00, sizeof(buf));
	
	if ( (fd=open(argv[1], O_RDONLY)) == -1)
		ERR_EXIT("open");
	
	for ( ; ; ) {
		if ( (ret=read(fd, buf, MAXLINE)) <= 0)
			break;
		fprintf(stdout, "%s", buf);
		fflush(stdout);
		memset(buf, 0x00, sizeof(buf));
		sleep(1);
	}
	
	if ( ret == -1 ) {
		close(fd);
		ERR_EXIT("read");
	}

	close(fd);
	
	return 0;
}

