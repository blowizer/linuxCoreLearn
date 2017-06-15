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

void f1(void) { printf("f1\n");}
void f2(void) { printf("f2\n");}

int main( void )
{
	atexit(f1);
	atexit(f2);

	printf("--------inter main---------!\n");
	printf("--------outer main---------!\n");

	return 0;
}

