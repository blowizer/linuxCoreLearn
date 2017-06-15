#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]%s", __FILE__, __LINE__, m, strerror(errno)); \
		exit(-1); \
	} while (0)

int main( int argc, char *argv[] )
{
	if ( argc != 2 ) {
		printf("%s file\n", argv[0]);
		exit(-1);
	}

	int ret;
	int fd;
	char buf[5] = {};

	if ( (fd=open(argv[1], O_RDONLY)) == -1)
		ERR_EXIT("open");
	
lab:
	lseek(fd, 0, SEEK_SET);
	while ( 1 ) {
		if ( (ret=read(fd, buf, 5)) <= 0)
			break;
		if ( write(2, buf, ret) != ret )
			ERR_EXIT("write");
		sleep(1);
		memset(buf, 0x00, sizeof(buf));
	}
goto lab;
	
	close(fd);
}

