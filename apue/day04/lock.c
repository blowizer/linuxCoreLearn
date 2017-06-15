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
	struct flock lock;
	
	memset(&lock, 0x00, sizeof(lock));
	
	fd=open("test.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
	if ( fd == -1)
		ERR_EXIT("open");
	
	lock.l_type   = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start  = 0;
	lock.l_len    = 0;

	if ( fcntl(fd, F_SETLKW, &lock) == 0)
		printf("加锁成功!\n");
	else
		ERR_EXIT("fcntl");
		
	printf("按任意键解锁!\n");
	getchar();
	
	lock.l_type = F_UNLCK;
	if ( fcntl(fd, F_SETLK, &lock) == 0)
		printf("解锁成功!\n");
	else
		ERR_EXIT("fcntl");
	
	close(fd);

	return 0;
}

