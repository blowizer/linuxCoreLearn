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

#define MAXLINE 1

int main( void )
{
	int fd;
	int ret;
	int index = 0;
	char buf[MAXLINE+1] = {};
	
	if ((fd=open("test.txt", O_RDONLY))==-1)
		ERR_EXIT("open");
	
	while ( 1 ) {
		/*
		if ((ret=read(fd, buf, MAXLINE)) <= 0 ) {
			if ( errno == EINTR)
				continue;
			break;
		}

		fprintf(stderr, "%s", buf);
		while ( lseek(fd, 1, SEEK_CUR) == -1) {
			if ( errno == EINTR)
				continue;
			ERR_EXIT("lseek");
		}
		*/
		if ( pread(fd, buf, MAXLINE, index) <= 0)
			break;
		fprintf(stderr, "%s", buf);
		index += 2;
		
		//printf("lseek=%d\n", lseek(fd, 0, SEEK_CUR));
		memset(buf, 0x00, sizeof(buf));
	}
	
	close(fd);

	return 0;
}
