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

void func1(int i, void *arg) {
	printf("%d arg %s\n", i, arg);
}

void func2(int i, void *arg) {
	printf("%d arg %s\n", i, arg);
}

int main( void )
{
	char *str = malloc(20);
	memcpy(str, "NB", 2);
	on_exit(func1, str);
	on_exit(func2, "lilei");

	return 2;
}

