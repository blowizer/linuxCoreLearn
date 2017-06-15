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
	fd=shm_open("/xyz", O_RDWR, 0);
	if ( fd == -1 )
		ERR_EXIT("shm_open");
	stu_t *p;
	p=mmap(NULL, sizeof(stu_t), PROT_WRITE, MAP_SHARED, fd, 0);
	if ( p == MAP_FAILED )
		ERR_EXIT("mmap");
	
	p->age = 18;
	strcpy(p->name, "贾旭");

	munmap(p, sizeof(stu_t));

	close(fd);
	return 0;
}

