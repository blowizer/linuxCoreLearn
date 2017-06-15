#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

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
	/*
	int *p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, 0, 0);
	if ( p == MAP_FAILED)
		ERR_EXIT("mmap");
	*p = 100;
	printf("*p=%d\n", *p);
	
	munmap(p, 4);
	
	*/

	while (1);

	return 0;
}

