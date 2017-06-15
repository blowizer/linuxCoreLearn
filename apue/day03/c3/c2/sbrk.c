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
	int *p = sbrk(0);
	/*
	if ( p == (void*)-1 )
		ERR_EXIT("sbrk");
	printf("p=%p\n", p);
	*p = 1000;
	int *q = sbrk(4096);
	printf("q=%p\n", q);
	q[1024] = 1324;
	*/
	
	printf("%p\n", p);
	brk(p+4);
	*p = 100;
	brk(p);
	*p = 200;
	
	/*
	*p = 1000;
	p[1] = 200;
	printf("*p=%d\n", *p);
	printf("p[1]=%d\n", p[1]);
	printf("p=%p\n", p);
	p[1024] = 300;
	*/
	
	while ( 1 );
	return 0;
}

