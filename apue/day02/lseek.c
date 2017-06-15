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

int main( void ) {
	int fd;
	int ret;
	int offset;
	char buf[10] = {};

	if ( (fd=open("test.txt", O_RDONLY)) == -1)
		ERR_EXIT("open");
	
	
	while ( (ret=read(fd, buf, 5)) <= 0 ) {
		if ( errno == EINTR )
			continue;
		break;
	}
	
	if ( ret == -1)
		ERR_EXIT("read");
	
	offset = lseek(fd, 0, SEEK_CUR);
	if ( offset == -1)
		ERR_EXIT("lseek");
	printf("offsert=%d\n", offset);
	
	close(fd);
	
	return 0;
}

