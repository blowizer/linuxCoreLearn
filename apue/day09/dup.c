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

int main( int argc, char *argv[] )
{
	if ( argc != 3 ) {
		fprintf(stderr, "usage %s src dest\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd1, fd2;
	if ( (fd1=open(argv[1], O_RDONLY)) == -1)
		ERR_EXIT("open");
	fd2=open(argv[2], O_WRONLY|O_CREAT|O_TRUNC|O_EXCL, 0644);
	if ( fd2 == -1)
		ERR_EXIT("open");
	dup2(fd1, 0);
	dup2(fd2, 1);
	execlp("cat", "cat", NULL);
	
	return 0;
}

