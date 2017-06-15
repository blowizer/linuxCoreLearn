#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do { \
		fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

typedef struct stu{
	char name[32];
	int age;
}stu_t;

int main( void )
{
	int fd;
	fd=shm_open("/xyz", O_RDWR|O_CREAT, 0666);
	if ( fd == -1 )
		ERR_EXIT("shm_open");
	printf("create success!\n");
	ftruncate(fd, sizeof(stu_t));
	return 0;
}

