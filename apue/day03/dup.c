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
	fd=open("furong", O_WRONLY);
	if ( fd == -1)
		ERR_EXIT("open");
	
	//close(1);
	//dup(fd);
	//dup2(fd, 1);
	close(1);
	fcntl(fd, F_DUPFD, 0);

	char *len= "how do you do!\n";
	write(1, len, strlen(len));

	close(fd);
	return 0;
}

