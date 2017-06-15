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
	int ret = -1;

	if ( (ret=close(10)) == -1 )
		//perror("close");
		//printf("[%s][%d]:close %s\n", __FILE__, __LINE__, strerror(errno));
		//printf("%m\n");
		ERR_EXIT("close");
	else
		printf("close successed!\n");

	return 0;
}

