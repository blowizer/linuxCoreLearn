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

int main( int argc, char *argv[] )
{
	if ( argc != 2) {
		fprintf(stderr, "%s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if ( unlink(argv[1]) == -1)
		ERR_EXIT("unlink");

	return 0;
}
