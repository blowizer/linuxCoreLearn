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
	pid_t pid;
	struct flock lock;
	
	memset(&lock, 0x00, sizeof(lock));
	
	lock.l_type   = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start  = 0;
	lock.l_len    = 0;

	fd=open("test.txt", O_WRONLY);
	if ( fd == -1 )
		ERR_EXIT("open");

	if ( (pid=fork()) == -1)
		ERR_EXIT("fork");
	
	if ( pid > 0 ) {
		lock.l_type   = F_WRLCK;
		if ( fcntl(fd, F_SETLKW, &lock) == -1)
			ERR_EXIT("fcntl");
		write(fd, "parent", 6);
		lock.l_type   = F_UNLCK;
		if ( fcntl(fd, F_SETLKW, &lock) == -1)
			ERR_EXIT("fcntl");
		
	} else {
		lock.l_type   = F_WRLCK;
		if ( fcntl(fd, F_SETLKW, &lock) == -1)
			ERR_EXIT("fcntl");
		write(fd, "child", 5);
		lock.l_type   = F_UNLCK;
		if ( fcntl(fd, F_SETLKW, &lock) == -1)
			ERR_EXIT("fcntl");
	}
	
	close(fd);
	return 0;
}

