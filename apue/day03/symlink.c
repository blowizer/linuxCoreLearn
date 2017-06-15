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
	if ( argc != 3 ) {
		fprintf(stderr, "%s src sym\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if ( symlink(argv[1], argv[2]) == -1)
		ERR_EXIT("symlink");
	
	return 0;
}
