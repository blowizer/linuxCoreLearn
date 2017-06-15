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
	int fd1;
	int fd2;
	char buf1[1024]  = {};
	char buf2[1024]  = {};

	if ( (fd1=open("furong", O_RDONLY)) == -1)
		ERR_EXIT("open");
	if ( (fd2=open("furong", O_RDWR)) == -1)
		ERR_EXIT("open");
	
	read(fd1, buf1, 5);
	read(fd2, buf2, 5);
	printf("buf1=%s\n", buf1);
	printf("buf2=%s\n", buf2);
	
	write(fd2, "AAAAA", 5);
	memset(buf1, 0x00, sizeof(buf1));
	read(fd1, buf1, 5);
	printf("buf1=%s\n", buf1);

	close(fd1);
	close(fd2);

	return 0;
}

